# zephyr-rtos

Experimental [Zephyr RTOS] bindings for Rust. It is not production ready, and at the moment serves more as a testing and experimenting project.

Currently supports the following Zephyr features:

  * Threads
  * Mutexes
  * Semaphores
  * Condition variables
  * `printk`
  * Rebooting

There are some ideas how to integrate Rust code with device-tree
generated code as well, but no work has started.

## Building

Only tested using nRF Connect SDK v2.6.1 (Zephyr version 3.5.99).

Only ARM targets are supported at the moment, and this has only been
tested on Cortex-M4 targets (nRF52840 and stm32g4).

The environment variable `RUST_ZEPHYR_CC_DB` must be set to
a complete path to a Zephyr `compile_commands.json` file. The Zephyr
toolchain must be installed in a location without spaces.

There are probably more limitations as well.

By using [Corrosion] we can build the Rust code from CMake
and link to it, allowing fairly simple integration of a Rust project
in a Zephyr application project.

[Corrosion]: https://corrosion-rs.github.io/corrosion/introduction.html
[Zephyr RTOS]: https://zephyrproject.org/

## Example: hello world

Lets adapt the basic `blinky` project, and add additional functionality using Rust.

First we create a new Rust library project: `cargo new --lib rust_hello`

We then change the `Cargo.toml` file to the following:

```toml
[package]
name = "rust_hello"
version = "0.1.0"
edition = "2021"

[lib]
name = "rust_hello"
crate-type = ["staticlib"]

[dependencies]
zephyr-rtos = { git = "TODO" }

[profile.dev]
panic="abort"
[profile.release]
panic="abort"
```

Change `lib.rs` to the following:

```rust
#![no_std]

// Print using printk from Zephyr
use zephyr_rtos::printk;
// Macro to define a thread at build time similar to K_THREAD_DEFINE
use zephyr_rtos::thread_define;

// Our thread entry function
extern "C" fn rust_thread(_: *mut core::ffi::c_void, _: *mut core::ffi::c_void, _: *mut core::ffi::c_void) {
    printk!("Starting rust thread\n");
    loop {
        zephyr_rtos::thread::sleep_ms(1000);
        printk!("Hello {} world\n", "formatting");
    }
}



thread_define!(HELLO_THREAD, 2048, crate::rust_thread);

// This must be called from `main` in the Zephyr project.
#[no_mangle]
pub extern "C" fn rust_init() {}

// Panic handler, simply print the error and reboot.
#[panic_handler]
fn on_panic(info: &core::panic::PanicInfo) -> ! {
    zephyr_rtos::printk!("{:?}", info);
    unsafe { zephyr_rtos::bindings::sys_reboot(0) };
}
```

Change `main.c` to the following:

```c
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void rust_init(void);

int main(void)
{
	int ret;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	rust_init();    // Note that this must be called for the Rust thread to start

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 0;
		}
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}

```

Add `CONFIG_CPP` to `prj.conf`

Finally change `CMakeLists.txt` of the Zephyr `blinky` project
to the following:

```cmake
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

target_sources(app PRIVATE
    src/main.c
)

# Adjust according to your target
set(Rust_CARGO_TARGET thumbv7em-none-eabi)

include(FetchContent)

FetchContent_Declare(
    Corrosion
    GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
    GIT_TAG v0.5
)
FetchContent_MakeAvailable(Corrosion)

# Adjust path according to your setup
corrosion_import_crate(MANIFEST_PATH ${CMAKE_CURRENT_LIST_DIR}/rust_hello/Cargo.toml
    NO_STD
    PROFILE release
)

corrosion_set_env_vars(rust_hello RUST_ZEPHYR_CC_DB=${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)

target_link_libraries(app PRIVATE rust_hello)
```
