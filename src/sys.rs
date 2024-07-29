
/// Reboot the target.
pub fn reboot(code: core::ffi::c_int) -> ! {
    unsafe { crate::bindings::sys_reboot(code) }
}