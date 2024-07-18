#![no_std]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(non_snake_case)]
#[doc(hidden)]
pub mod bindings;

pub mod print;
pub mod sync;
pub mod thread;
pub mod time;

pub(crate) mod macros;

mutex_define!(COUNT: i32 = 0);

/// `print` style macro but uses Zephyrs `printk` instead.
#[macro_export]
macro_rules! printk {
    () => {
    };
    ($($arg:tt)*) => {
        {
            use core::fmt::Write;
            let mut __printk_writer = $crate::print::PrintKWriter;
            let _ = core::write!(__printk_writer, $($arg)*);
        }
    };
}

#[no_mangle]
pub extern "C" fn rust_thread(num: core::ffi::c_int) {
    loop {
        let mut count = COUNT.lock();
        *count += 1;
        printk!("Thread {}, count = {}\n", num, *count);
        unsafe { bindings::k_msleep(1000) };
        printk!("Thread {}, releasing lock\n", num);
    }
}

extern "C" fn test_thread_main(
    _: *mut core::ffi::c_void,
    _: *mut core::ffi::c_void,
    _: *mut core::ffi::c_void,
) {
    let name = unsafe {
        let current = crate::bindings::k_current_get();
        let name = crate::bindings::k_thread_name_get(current);
        if name.is_null() {
            "<NULL>"
        } else {
            core::ffi::CStr::from_ptr(name)
                .to_str()
                .unwrap_or("<INVALID>")
        }
    };
    use crate::printk;
    loop {
        let mut count = COUNT.lock();
        *count += 1;
        printk!("Rust thread '{}', count = {}\n", name, *count);
        unsafe { bindings::k_msleep(1000) };
        printk!("Rust thread '{}' releasing lock\n", name);
    }
}

thread_define!(rust_test_thread, 2048, test_thread_main);

#[cfg(not(test))]
mod not_test {
    #[panic_handler]
    fn on_panic(info: &core::panic::PanicInfo) -> ! {
        printk!("{:?}", info);
        loop {}
    }
}
