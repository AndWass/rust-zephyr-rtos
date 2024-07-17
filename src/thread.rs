use core::{cell::UnsafeCell, ffi::CStr};

const fn stack_align() -> usize {
    if crate::bindings::MPU_GUARD_ALIGN_AND_SIZE > crate::bindings::MPU_GUARD_ALIGN_AND_SIZE_FLOAT {
        crate::bindings::MPU_GUARD_ALIGN_AND_SIZE as usize
    } else {
        crate::bindings::MPU_GUARD_ALIGN_AND_SIZE_FLOAT as usize
    }
}

const STACK_ALIGN: usize = stack_align();
pub const STACK_RESERVED: usize = crate::bindings::ARCH_KERNEL_STACK_RESERVED as usize;

#[repr(C)]
pub struct ThreadStack<const SIZE: usize> {
    _data: [crate::bindings::z_thread_stack_element; SIZE],
    _align: elain::Align<STACK_ALIGN>,
}

impl<const SIZE: usize> ThreadStack<SIZE> {
    pub const fn new() -> Self {
        assert!(SIZE > (crate::bindings::ARCH_KERNEL_STACK_RESERVED as usize));
        assert!(
            (SIZE - crate::bindings::ARCH_KERNEL_STACK_RESERVED as usize)
                % (crate::bindings::ARCH_STACK_PTR_ALIGN as usize)
                == 0
        );
        Self {
            _data: [unsafe { core::mem::zeroed() }; SIZE],
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

#[macro_export]
macro_rules! thread_define {
    ($name:ident, $stack:literal, $entry:ident) => {
        mod __thread {
            pub(super) mod $name {
                #[used]
                #[link_section = ".noinit.__rust.0"]
                pub static STACK: crate::thread::ThreadStack<
                    { $stack + crate::thread::STACK_RESERVED },
                > = crate::thread::ThreadStack::new();
                pub static THREAD_OBJ: crate::thread::KThreadObj = crate::thread::KThreadObj::new();
            }
        }
        #[used]
        #[link_section = ".__static_thread_data.static.__rust"]
        pub static $name: crate::thread::KStaticThreadData = unsafe {
            crate::thread::KStaticThreadData::new(
                &__thread::$name::THREAD_OBJ,
                &__thread::$name::STACK,
                $entry,
                7,
                0,
                core::ffi::CStr::from_bytes_with_nul_unchecked(
                    concat!(stringify!($name), '\0').as_bytes(),
                ),
                crate::time::K_NO_WAIT,
            )
        };
    };
}
