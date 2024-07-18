use core::{cell::UnsafeCell, ffi::CStr};

const fn thread_stack_alignment() -> usize {
    if crate::bindings::MPU_GUARD_ALIGN_AND_SIZE > crate::bindings::MPU_GUARD_ALIGN_AND_SIZE_FLOAT {
        crate::bindings::MPU_GUARD_ALIGN_AND_SIZE as usize
    } else {
        crate::bindings::MPU_GUARD_ALIGN_AND_SIZE_FLOAT as usize
    }
}

const THREAD_STACK_ALIGNMENT: usize = thread_stack_alignment();

pub const STACK_SIZE_ALIGNMENT: usize = crate::bindings::ARCH_STACK_PTR_ALIGN as usize;
/// The size of the Zephyr reserved portion of a thread stack.
///
/// The reserved portion is not used as stack data.
pub const STACK_RESERVED: usize = crate::bindings::ARCH_KERNEL_STACK_RESERVED as usize;

/// Represents a stack for thread usage.
///
/// `SIZE` is the size of the stack for the thread.
///
#[repr(C)]
pub struct ThreadStack<const SIZE: usize> {
    _data: [crate::bindings::z_thread_stack_element; SIZE],
    _reserved: [crate::bindings::z_thread_stack_element; STACK_RESERVED],
    _align: elain::Align<THREAD_STACK_ALIGNMENT>,
}

impl<const SIZE: usize> ThreadStack<SIZE> {
    /// Create a new [`ThreadStack`] with a total size of `SIZE`.
    ///
    /// # Panic
    ///
    /// The function will panic in if `SIZE` fails any of these assertions:
    ///
    ///   * `SIZE > 0`
    ///   * [`SIZE % STACK_SIZE_ALIGNMENT == 0`](STACK_SIZE_ALIGNMENT)
    pub const fn new() -> Self {
        assert!(SIZE > 0);
        assert!(SIZE % STACK_SIZE_ALIGNMENT == 0);
        Self {
            _data: [unsafe { core::mem::zeroed() }; SIZE],
            _reserved: [unsafe { core::mem::zeroed() }; STACK_RESERVED],
            _align: elain::Align::NEW,
        }
    }
}

#[repr(C)]
pub struct KThreadObj {
    thread: UnsafeCell<crate::bindings::k_thread>,
}

impl KThreadObj {
    pub const fn new() -> Self {
        Self {
            thread: UnsafeCell::new(unsafe { core::mem::zeroed() }),
        }
    }
}

unsafe impl Send for KThreadObj {}
unsafe impl Sync for KThreadObj {}

#[repr(C)]
pub struct KStaticThreadData {
    data: crate::bindings::_static_thread_data,
}

impl KStaticThreadData {
    pub const unsafe fn new<const STACK_SIZE: usize>(
        thread_obj: &'static KThreadObj,
        stack: &'static ThreadStack<STACK_SIZE>,
        entry: extern "C" fn(
            *mut core::ffi::c_void,
            *mut core::ffi::c_void,
            *mut core::ffi::c_void,
        ),
        init_prio: i32,
        init_options: u32,
        name: &'static CStr,
        init_delay: crate::time::Timeout,
    ) -> Self {
        Self {
            data: crate::bindings::_static_thread_data {
                init_thread: thread_obj.thread.get(),
                init_stack: stack._data.as_ptr() as *mut _,
                init_stack_size: STACK_SIZE as u32,
                init_entry: Some(entry),
                init_p1: core::ptr::null_mut(),
                init_p2: core::ptr::null_mut(),
                init_p3: core::ptr::null_mut(),
                init_prio,
                init_options,
                init_name: name.as_ptr(),
                init_delay,
            },
        }
    }
}

unsafe impl Send for KStaticThreadData {}
unsafe impl Sync for KStaticThreadData {}

#[derive(Copy, Clone)]
enum ThreadRef<'a> {
    Ref(&'a KThreadObj),
    Current,
}

pub struct Thread<'a> {
    ref_obj: ThreadRef<'a>,
}

impl<'a> Thread<'a> {
    fn k_thread_ptr(&self) -> *mut crate::bindings::k_thread {
        match self.ref_obj {
            ThreadRef::Ref(r) => r.thread.get(),
            ThreadRef::Current => unsafe { crate::bindings::k_current_get() },
        }
    }
    pub const fn new(k_thread: &'a KThreadObj) -> Self {
        Self {
            ref_obj: ThreadRef::Ref(k_thread),
        }
    }

    pub const fn current() -> Self {
        Self {
            ref_obj: ThreadRef::Current,
        }
    }

    pub fn name(&'a self) -> Option<&'a CStr> {
        let name = unsafe { crate::bindings::k_thread_name_get(self.k_thread_ptr()) };
        if name.is_null() {
            None
        } else {
            unsafe { Some(core::ffi::CStr::from_ptr(name)) }
        }
    }

    pub fn try_join(&self) -> Result<(), core::ffi::c_int> {
        let res =
            unsafe { crate::bindings::k_thread_join(self.k_thread_ptr(), crate::time::K_FOREVER) };
        if res == 0 {
            Ok(())
        } else {
            Err(res)
        }
    }

    pub fn join(&self) {
        self.try_join().unwrap();
    }

    pub fn get_priority(&self) -> core::ffi::c_int {
        unsafe { crate::bindings::k_thread_priority_get(self.k_thread_ptr()) }
    }
}

unsafe impl<'a> Send for Thread<'a> {}
unsafe impl<'a> Sync for Thread<'a> {}

#[macro_export]
macro_rules! thread_define {
    ($name:ident, $stack:literal, $entry:path) => {
        mod __thread {
            pub(super) mod $name {
                #[used]
                #[link_section = ".noinit.__rust.0"]
                pub static STACK: crate::thread::ThreadStack<$stack> =
                    crate::thread::ThreadStack::new();
                pub static THREAD_OBJ: crate::thread::KThreadObj = crate::thread::KThreadObj::new();
                #[used]
                #[link_section = ".__static_thread_data.static.__rust"]
                pub static $name: crate::thread::KStaticThreadData = unsafe {
                    crate::thread::KStaticThreadData::new(
                        &THREAD_OBJ,
                        &STACK,
                        $entry,
                        7,
                        0,
                        core::ffi::CStr::from_bytes_with_nul_unchecked(
                            concat!(stringify!($name), '\0').as_bytes(),
                        ),
                        crate::time::K_NO_WAIT,
                    )
                };
            }
        }
        #[used]
        static $name: $crate::thread::Thread<'static> =
            $crate::thread::Thread::new(&__thread::$name::THREAD_OBJ);
    };
}
