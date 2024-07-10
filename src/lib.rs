#![no_std]

#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
#![allow(non_snake_case)]
#[doc(hidden)]
pub mod bindings;

pub mod sync;
pub mod time;
pub mod print;

#[doc(hidden)]
pub mod macros;

mutex_define!(COUNT: i32 = 0);

/// `print` style macro but uses Zephyrs `printk` instead.
#[macro_export]
macro_rules! printk {
    () => {
    };
    ($($arg:tt)*) => {
        {
            use core::fmt::Write;
            let mut __printk_writer = $crate::print::Writer;
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

#[cfg(not(test))]
mod not_test {
    #[panic_handler]
    fn on_panic(info: &core::panic::PanicInfo) -> ! {
        printk!("{:?}", info);
        loop {}
    }
}
