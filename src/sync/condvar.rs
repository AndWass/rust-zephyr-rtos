use super::{KMutexGuard, MutexGuard};

/// Result of a wait on a [`KCondVar`] condition variable.
pub enum KWaitResult<'a> {
    /// The thread woke up due to a notification.
    Notified(KMutexGuard<'a>),
    /// The thread woke up due to a wait timeout.
    Timeout(KMutexGuard<'a>),
}
pub struct KCondvar {
    k_cv: crate::bindings::k_condvar,
}

impl KCondvar {
    fn k_cv_ptr(&self) -> *mut crate::bindings::k_condvar {
        &self.k_cv as *const _ as *mut _
    }
    /// Create a new [`KCondVar`]
    ///
    /// Prefer to use the macro [`k_condvar_define`] to define a static condition variable instead.
    ///
    /// [`k_condvar_define`]: crate::k_condvar_define
    ///
    /// [`KCondVar::init`] must be called before this can be used, unless the semaphore was
    /// created with [`k_condvar_define`].
    ///
    pub fn new() -> Self {
        Self {
            k_cv: unsafe { core::mem::zeroed() },
        }
    }

    /// Create a new static `KCondVar`.
    ///
    /// `this` must refer to a `static KCondVar` instance that the return value is assigned to.
    ///
    /// # Safety
    ///
    /// **Do not use directly**
    ///
    ///   * Should not be used by user code. Use [`k_condvar_define`] instead!
    ///   * Must only be used on the following form: `static CV: KCondVar = unsafe { KCondVar::new_static(&CV) };`
    ///
    pub const unsafe fn new_static(this: &'static Self) -> Self {
        Self {
            k_cv: crate::bindings::k_condvar {
                wait_q: crate::macros::__init_wait_q_t!(this.k_cv.wait_q),
            },
        }
    }

    /// Initialize the [`KCondVar`], making it ready to use.
    ///
    /// Only needs to be called on condition variables created via [`KCondVar::new`].
    ///
    /// # Safety
    ///
    ///   * After `init` the semaphore must not be moved, it must be treated as if pinned.
    ///
    /// # Panic
    ///
    /// Panics if the call to `k_condvar_init` fails.
    pub unsafe fn init(&mut self) {
        let res = crate::bindings::k_condvar_init(self.k_cv_ptr());
        if res != 0 {
            panic!("k_sem_init failed: {}", res);
        }
    }

    /// Wakes up one blocked thread on this condition variable.
    ///
    /// # Safety
    ///
    /// The condition variable must be ready for use, either by [`init`](KCondVar::init) being called,
    /// or by statically defining the condition variable with [`k_condvar_define`]
    pub unsafe fn notify_one(&self) {
        crate::bindings::k_condvar_signal(self.k_cv_ptr());
    }

    /// Wakes up all blocked thread on this condition variable.
    ///
    /// # Safety
    ///
    /// The condition variable must be ready for use, either by [`init`](KCondVar::init) being called,
    /// or by statically defining the condition variable with [`k_condvar_define`]
    pub unsafe fn notify_all(&self) {
        crate::bindings::k_condvar_broadcast(self.k_cv_ptr());
    }

    /// Wait with a timeout
    ///
    /// Waits until the thread is either notified, or a timeout has occurred.
    ///
    /// # Safety
    ///
    /// The condition variable must be ready for use, either by [`init`](KCondVar::init) being called,
    /// or by statically defining the condition variable with [`k_condvar_define`]
    pub unsafe fn wait_timeout<'a>(
        &self,
        mutex_guard: KMutexGuard<'a>,
        timeout: crate::time::Timeout,
    ) -> KWaitResult<'a> {
        let res =
            crate::bindings::k_condvar_wait(self.k_cv_ptr(), mutex_guard.k_mutex_ptr(), timeout);
        if res == 0 {
            KWaitResult::Notified(mutex_guard)
        } else {
            KWaitResult::Timeout(mutex_guard)
        }
    }
}

unsafe impl Send for KCondvar {}
unsafe impl Sync for KCondvar {}

/// Statically initialize a [`KCondVar`] instances.
///
/// This is the preferred method for creating [`KCondVar`] instances.
/// This statically initializes the condition variable, and ensures it is ready for use immediately.
#[macro_export]
macro_rules! k_condvar_define {
    ($name:ident $($vis:tt)*) => {
        #[used]
        #[link_section = "._k_condvar.static.__rust"]
        $($vis)* static $name: $crate::sync::KCondvar = unsafe { $crate::sync::KCondvar::new_static(&$name) };
    };
}

pub struct Condvar {
    cv: *const KCondvar,
}

impl Condvar {
    fn cv_ref(&self) -> &KCondvar {
        unsafe { &*self.cv }
    }

    /// Create a new condition variable from a [`KCondvar`] reference.
    ///
    /// # Safety
    ///
    ///   * `cv` must be fully initialized, such that `cv.wait_timeout(...)` is valid. See [`KCondvar::wait_timeout`].
    ///   * `cv` must outlive the created mutex.
    ///   * `cv` must not be moved to a different location.
    ///
    pub const unsafe fn new_unchecked(cv: &KCondvar) -> Self {
        Self { cv }
    }

    /// Notify one thread to wake up.
    pub fn notify_one(&self) {
        // SAFETY:
        // The `new_unchecked` safety requirements makes sure this is valid
        unsafe { self.cv_ref().notify_one() }
    }

    /// Notify all waiting threads to wake up.
    pub fn notify_all(&self) {
        // SAFETY:
        // The `new_unchecked` safety requirements makes sure this is valid
        unsafe { self.cv_ref().notify_all() }
    }

    /// Wait until the thread is woken up by the condition variable.
    pub fn wait<'a, T>(&self, guard: MutexGuard<'a, T>) -> MutexGuard<'a, T> {
        let (mutex, k_guard) = guard.into_inner();
        // SAFETY:
        // The `new_unchecked` safety requirements makes sure this is valid
        let wait_res = unsafe { self.cv_ref().wait_timeout(k_guard, crate::time::K_FOREVER) };
        let k_guard = match wait_res {
            KWaitResult::Notified(x) => x,
            KWaitResult::Timeout(x) => x,
        };

        MutexGuard::from_mutex_and_guard(mutex, k_guard)
    }

    /// Blocks the current thread until this condition variable receives a
    /// notification and the provided condition is false.
    pub fn wait_while<'a, T, F>(
        &self,
        mut guard: MutexGuard<'a, T>,
        mut condition: F,
    ) -> MutexGuard<'a, T>
    where
        F: FnMut(&mut T) -> bool,
    {
        while condition(&mut *guard) {
            guard = self.wait(guard);
        }

        guard
    }
}

unsafe impl Send for Condvar {}
unsafe impl Sync for Condvar {}

/// Statically initialize a [`Condvar`] instances.
///
/// This is the preferred method for creating [`Condvar`] instances.
/// This statically initializes the condvar, and ensures it is ready for use immediately, upholding all necessary safety guarantees.
#[macro_export]
macro_rules! condvar_define {
    ($name:ident) => {
        $crate::concat_idents!(mod_name = __zephyr_sem_, $name {
            #[allow(non_snake_case)]
            mod mod_name {
                $crate::k_condvar_define!($name, $count, $limit pub(super));
            }
            static $name: $crate::sync::Condvar = unsafe { $crate::sync::Condvar::new_unchecked(&mod_name::$name) };
        });
    };
}
