#[repr(C)]
pub struct KSemaphore {
    k_sem: crate::bindings::k_sem,
}

impl KSemaphore {
    fn k_sem_ptr(&self) -> *mut crate::bindings::k_sem {
        &self.k_sem as *const _ as *mut _
    }

    /// Create a new [`KSemaphore`]
    ///
    /// Prefer to use the macro [`k_sem_define`] to define a static semaphore instead.
    ///
    /// [`k_sem_define`]: crate::k_sem_define
    ///
    /// [`KSemaphore::init`] must be called before this can be used, unless the semaphore was
    /// created with [`k_sem_define`].
    ///
    pub fn new() -> Self {
        Self {
            k_sem: unsafe { core::mem::zeroed() },
        }
    }

    /// Create a new static `KSemaphore`.
    ///
    /// `this` must refer to a `static KSemaphore` instance that the return value is assigned to.
    ///
    /// # Safety
    ///
    /// **Do not use directly**
    ///
    ///   * Should not be used by user code. Use [`k_sem_define`] instead!
    ///   * Must only be used on the following form: `static SEM: KSemaphore = unsafe { KSemaphore::new_static(&SEM) };`
    ///
    pub const unsafe fn new_static(this: &'static Self, count: u32, limit: u32) -> Self {
        assert!(limit != 0 && count <= limit, "Invalid semaphore limits");
        Self {
            k_sem: crate::bindings::k_sem {
                wait_q: crate::macros::__init_wait_q_t!(this.k_sem.wait_q),
                count: count,
                limit: limit,
            },
        }
    }

    /// Initialize the [`KSemaphore`], making it ready to use.
    ///
    /// Only needs to be called on semaphores created via [`KSemaphore::new`].
    ///
    /// # Safety
    ///
    ///   * After `init` the semaphore must not be moved, it must be treated as if pinned.
    ///
    /// # Panic
    ///
    /// Panics if the call to `k_sem_init` fails.
    pub unsafe fn init(&mut self, initial: u32, limit: u32) {
        let res = crate::bindings::k_sem_init(self.k_sem_ptr(), initial, limit);
        if res != 0 {
            panic!("k_sem_init failed: {}", res);
        }
    }

    /// Give one to the semaphore
    ///
    /// # Safety
    ///
    ///   * If the semaphore is created via [`KSemaphore::new`] then [`KSemaphore::init`] must be called first
    pub unsafe fn give(&self) {
        crate::bindings::k_sem_give(self.k_sem_ptr());
    }

    /// Take one from the semaphore.
    ///
    /// This will block until an item is available in the semaphore.
    ///
    /// # Safety
    ///
    ///   * If the semaphore is created via [`KSemaphore::new`] then [`KSemaphore::init`] must be called first
    pub unsafe fn take(&self) {
        loop {
            let res = crate::bindings::k_sem_take(self.k_sem_ptr(), crate::time::K_FOREVER);
            if res == -(crate::bindings::EAGAIN as i32) {
                continue;
            } else {
                break;
            }
        }
    }

    /// Try taking from the semaphore without blocking.
    ///
    /// Returns `true` if the semaphore was successfully taken.
    ///
    /// # Safety
    ///
    ///   * If the semaphore is created via [`KSemaphore::new`] then [`KSemaphore::init`] must be called first
    pub unsafe fn try_take(&self) -> bool {
        let res = crate::bindings::k_sem_take(self.k_sem_ptr(), crate::time::K_NO_WAIT);
        res == 0
    }

    /// Reset the semaphore.
    ///
    /// # Safety
    ///
    ///   * If the semaphore is created via [`KSemaphore::new`] then [`KSemaphore::init`] must be called first
    pub unsafe fn reset(&self) {
        crate::bindings::k_sem_reset(self.k_sem_ptr());
    }
}

unsafe impl Send for KSemaphore {}
unsafe impl Sync for KSemaphore {}

/// Statically initialize [`KSemaphore`] instances.
///
/// This is the preferred method for creating [`KSemaphore`] instances.
/// This statically initializes the semaphore, and ensures it is ready for use immediately.
#[macro_export]
macro_rules! k_sem_define {
    ($name:ident, $count:literal, $limit:literal $($vis:tt)*) => {
        #[used]
        #[link_section = "._k_sem.static.__rust"]
        $($vis)* static $name: $crate::sync::KSemaphore = unsafe { $crate::sync::KSemaphore::new_static(&$name, $count, $limit) };
    };
}

pub struct Semaphore {
    sem: *const KSemaphore,
}

impl Semaphore {
    fn sem_ref(&self) -> &KSemaphore {
        unsafe { &*self.sem }
    }

    /// Create a new semaphore from a [`KSemaphore`] reference.
    ///
    /// # Safety
    ///
    ///   * `sem` must be fully initialized, such that `sem.give()` is valid. See [`KSemaphore::give`].
    ///   * `sem` must outlive the created mutex.
    ///   * `sem` must not be moved to a different location.
    ///
    pub const unsafe fn new_unchecked(sem: &KSemaphore) -> Self {
        Self { sem }
    }

    /// Give one to the semaphore
    pub fn give(&self) {
        // SAFETY:
        // The `new_unchecked` safety requirements makes sure this is valid
        unsafe { self.sem_ref().give() }
    }

    /// Take one from the semaphore.
    ///
    /// This will block until the semaphore is available to be taken.
    pub fn take(&self) {
        // SAFETY:
        // The `new_unchecked` safety requirements makes sure this is valid
        unsafe { self.sem_ref().take() }
    }

    /// Try to take one from the semaphore.
    ///
    /// This will never block.
    pub fn try_take(&self) -> bool {
        // SAFETY:
        // The `new_unchecked` safety requirements makes sure this is valid
        unsafe { self.sem_ref().try_take() }
    }

    /// Reset the semaphore.
    pub fn reset(&self) {
        // SAFETY:
        // The `new_unchecked` safety requirements makes sure this is valid
        unsafe { self.sem_ref().reset() }
    }
}

unsafe impl Send for Semaphore {}
unsafe impl Sync for Semaphore {}

/// Statically initialize a [`Semaphore`] instances.
///
/// This is the preferred method for creating [`Semaphore`] instances.
/// This statically initializes the semaphore, and ensures it is ready for use immediately, upholding all necessary safety guarantees.
#[macro_export]
macro_rules! semaphore_define {
    ($name:ident, $count:literal, $limit:literal) => {
        mod __zsemaphore_backer {
            $crate::k_sem_define!($name, $count, $limit pub(super));
        }
        static $name: $crate::sync::Semaphore = unsafe { $crate::sync::Semaphore::new_unchecked(&__zsemaphore_backer::$name) };
    };
}
