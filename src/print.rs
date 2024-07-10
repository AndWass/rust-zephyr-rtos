use crate::bindings::printk as z_printk;

pub fn printk(data: &str) {
    const BUF_SIZE: usize = 33;
    let mut buf = heapless::Vec::<u8, BUF_SIZE>::new();
    let mut left_to_print = data.as_bytes();

    while !left_to_print.is_empty() {
        buf.clear();
        if left_to_print.len() < BUF_SIZE - 1 {
            let _ = buf.extend_from_slice(left_to_print);
            left_to_print = &[];
        }
        else {
            let _ = buf.extend_from_slice(&left_to_print[0..32]);
            left_to_print = &left_to_print[32..];
        }

        let _ = buf.push(0);
        unsafe { z_printk(b"%s\0".as_ptr() as *const core::ffi::c_char, buf.as_ptr()) };
    }
}

pub struct Writer;

impl core::fmt::Write for Writer {
    fn write_str(&mut self, s: &str) -> core::fmt::Result {
        printk(s);
        Ok(())
    }
}
