use crate::bindings::k_timeout_t;

pub type Timeout = k_timeout_t;

pub const K_FOREVER: Timeout = Timeout {
    ticks: -1 as crate::bindings::k_ticks_t
};

pub const K_NO_WAIT: Timeout = Timeout {
    ticks: 0
};