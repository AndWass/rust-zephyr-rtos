use crate::bindings::{k_mutex_init, k_mutex_lock, k_mutex_unlock};

use core::cell::UnsafeCell;
use core::marker::PhantomData;
use core::ops::{Deref, DerefMut};

/// Struct representing a zephyr mutex.
///
/// This is a very thin wrapper around a `k_mutex`.
#[repr(C)]
pub struct KMutex {
    /// For private use only. Touching this outside documented ways
    /// results in undefined behaviour.
    ///
    /// TODO: Explore how this could be made into an UnsafeCell.
    #[doc(hidden)]
    pub __priv: crate::bindings::k_mutex,
}

impl KMutex {
    fn k_mutex_ptr(&self) -> *mut crate::bindings::k_mutex {
        &self.__priv as *const _ as *mut _
    }

    // Safety requirements:
    // Lock must be held and must be called from the same thread that holds the lock.
    unsafe fn unlock(&self) {
        k_mutex_unlock(self.k_mutex_ptr());
    }

    /// Create a new `KMutex`
    ///
    /// Prefer to use the macro [`k_mutex_define`] to define a static mutex instead.
    ///
    /// [`k_mutex_define`]: crate::k_mutex_define
    ///
    /// [`KMutex::init`] must be called before this can be used.
    pub fn new() -> Self {
        Self {
            __priv: unsafe { core::mem::zeroed() },
        }
    }

    /// Initialize the [`KMutex`], making it ready to use.
    ///
    /// Only needs to be called on mutexes created via [`KMutex::new`].
    ///
    /// [`k_mutex_define`]: crate::k_mutex_define
    ///
    /// # Safety
    ///
    ///   * After `init` the mutex must not be moved, it must be treated as if pinned.
    ///
    /// # Panic
    ///
    /// Panics if the call to `k_mutex_init` fails.
    pub unsafe fn init(&mut self) {
        let res = unsafe { k_mutex_init(&mut self.__priv) };
        if res != 0 {
            panic!("k_mutex_init failed: {}", res);
        }
    }

    /// Lock the mutex
    ///
    /// # Safety
    ///
    ///   * If the mutex is created via [`KMutex::new`] then [`KMutex::init`] must be called first
    ///
    /// # Returns
    ///
    /// A lock guard that will automatically unlock the mutex on drop.
    ///
    pub unsafe fn lock(&self, timeout: crate::time::Timeout) -> Result<KMutexGuard, i32> {
        let res = k_mutex_lock(self.k_mutex_ptr(), timeout);
        if res == 0 {
            Ok(KMutexGuard {
                mutex: self,
                _ph: PhantomData,
            })
        } else {
            Err(res)
        }
    }
}

unsafe impl Send for KMutex {}
unsafe impl Sync for KMutex {}

/// Statically initialize [`KMutex`] instances.
///
/// This is the preferred method for creating [`KMutex`] instances.
/// This statically initializes the mutex, and ensures it is ready for use immediately.
#[macro_export]
macro_rules! k_mutex_define {
    ($name:ident $($vis:tt)*) => {
        #[used]
        #[link_section = "._k_mutex.static.__rust"]
        $($vis)* static $name: $crate::sync::KMutex = $crate::sync::KMutex {
            __priv: $crate::bindings::k_mutex {
                wait_q: $crate::__init_wait_q_t!($name.__priv.wait_q),
                owner: core::ptr::null_mut(),
                lock_count: 0,
                owner_orig_prio: $crate::bindings::K_LOWEST_APPLICATION_THREAD_PRIO as i32
            }
        };
    };
}

/// Drop guard for a [`KMutex`]
///
/// The referenced [`KMutex`] will automatically unlock on drop.
pub struct KMutexGuard<'a> {
    mutex: &'a KMutex,
    _ph: PhantomData<*mut ()>,
}

impl<'a> Drop for KMutexGuard<'a> {
    fn drop(&mut self) {
        // SAFETY:
        // the only way to obtain a KMutexGuard is via the `KMutex::lock` method,
        // and this is the only place where unlock is called.
        unsafe { self.mutex.unlock() };
    }
}

/// A `std::sync::Mutex` like object utilizing a [`KMutex`] as the mutex primitive.
pub struct Mutex<T> {
    mutex: *const KMutex,
    data: UnsafeCell<T>,
}

impl<T> Mutex<T> {
    fn zephyr_mutex_ref(&self) -> &KMutex {
        unsafe { &*self.mutex }
    }

    /// Create a new mutex from a [`KMutex`] reference.
    ///
    /// # Safety
    ///
    ///   * `k_mutex` must be fully initialized, such that `mutex.lock()` is valid. See [`KMutex::lock`].
    ///   * `k_mutex` must outlive the created mutex.
    ///   * `k_mutex` must not be moved to a different location.
    ///
    pub const unsafe fn new_unchecked(k_mutex: &KMutex, data: T) -> Self {
        Self {
            mutex: k_mutex,
            data: UnsafeCell::new(data),
        }
    }

    /// Lock the [`Mutex`], returning a [`MutexGuard`].
    ///
    /// This method will block and not return until the mutex has been acquired.
    ///
    /// # Panic
    ///
    /// Panics if the [`KMutex`] fails to lock for some reason.
    pub fn lock(&self) -> MutexGuard<T> {
        // SAFETY:
        // The `new_unchecked` method requires the `KMutex` to be initialized.
        let z_guard = unsafe { self.zephyr_mutex_ref().lock(crate::time::K_FOREVER) }.unwrap();

        MutexGuard {
            mutex: self,
            _drop_guard: z_guard,
            _ph: PhantomData,
        }
    }

    /// Try to lock the [`Mutex`], returning a [`MutexGuard`] if successful.
    ///
    /// This method will never block.
    pub fn try_lock(&self) -> Option<MutexGuard<T>> {
        // SAFETY:
        // The `new_unchecked` method requires the `KMutex` to be initialized.
        let z_guard = unsafe { self.zephyr_mutex_ref().lock(crate::time::K_NO_WAIT) }.ok()?;

        Some(MutexGuard {
            mutex: self,
            _drop_guard: z_guard,
            _ph: PhantomData,
        })
    }
}

unsafe impl<T: Send> Send for Mutex<T> {}
unsafe impl<T: Send> Sync for Mutex<T> {}

pub struct MutexGuard<'a, T> {
    mutex: &'a Mutex<T>,
    _drop_guard: KMutexGuard<'a>,
    _ph: PhantomData<*mut ()>,
}

impl<'a, T> Deref for MutexGuard<'a, T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        // SAFETY:
        // data is protected by a mutex
        unsafe { &*self.mutex.data.get() }
    }
}

impl<'a, T> DerefMut for MutexGuard<'a, T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        // SAFETY:
        // data is protected by a mutex
        unsafe { &mut *self.mutex.data.get() }
    }
}

/// Statically initialize [`Mutex`] instances.
///
/// This is the preferred method for creating [`Mutex`] instances.
/// This statically initializes the mutex, and ensures it is ready for use immediately.
#[macro_export]
macro_rules! mutex_define {
    ($name:ident: $typ:ty = $init:expr) => {
        mod __zmutex_backer {
            $crate::k_mutex_define!($name pub(super));
        }
        static $name: $crate::sync::Mutex<$typ> = unsafe { $crate::sync::Mutex::new_unchecked(&__zmutex_backer::$name, $init) };
    };
}
