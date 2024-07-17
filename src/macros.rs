macro_rules! __init_dnode {
    ($($init:tt)+) => {
        $crate::bindings::_dnode {
            __bindgen_anon_1: $crate::bindings::_dnode__bindgen_ty_1 {
                head: &$($init)+ as *const _ as *mut _,
            },
            __bindgen_anon_2: $crate::bindings::_dnode__bindgen_ty_2 {
                tail: &$($init)+ as *const _ as *mut _,
            }
        }
    }
}

macro_rules! __init_wait_q_t {
    ($($init:tt)+) => {
        $crate::bindings::_wait_q_t {
            waitq: $crate::macros::__init_dnode!($($init)+.waitq),
        }
    }
}

pub(crate) use __init_dnode;
pub(crate) use __init_wait_q_t;
