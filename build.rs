extern crate bindgen;

use std::env;
use std::path::{Path, PathBuf};

fn flag_filter(input: &&str) -> bool {
    input.starts_with("-D") || input.starts_with("-I")
    || input.starts_with("-mcpu") || input.starts_with("-mthumb") || input.starts_with("--sysroot")
    || input.starts_with("-mabi")
}

fn build_bridge(cmd: &str) {
    let mut skip_next = false;
    let filtered: Vec<_> = cmd.split(' ').filter(|x| {
        if skip_next {
            skip_next = false;
            false
        }
        else if *x == "-c" || *x == "-o" {
            skip_next = true;
            false
        }
        else {
            skip_next = false;
            true
        }
    }).collect();
    let cmd = filtered[0];
    let args = filtered.iter().skip(1);
}

fn main() {
    // Tell cargo to invalidate the built crate whenever the wrapper changes
    let out_dir = env::var_os("OUT_DIR").unwrap();


    println!("cargo::rerun-if-changed=wrapper.h");
    let compile_commands =
        json::parse(&std::fs::read_to_string(env::var("ZEPHYR_CC_DB").unwrap()).unwrap()).unwrap();
    let args = compile_commands[0]["command"]
        .as_str()
        .unwrap()
        .split(" ")
        .filter(flag_filter);
    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .wrap_static_fns(true)
        .wrap_static_fns_path(Path::new(&out_dir).join("bridge"))
        .use_core()
        .detect_include_paths(true)
        .detect_include_paths(true)
        .clang_args(args)
        .clang_arg("--target=arm-unknown-none-eabi")
        .header("wrapper.h")
        .generate()
        .expect("Unable to generate bindings");

    let out_path = Path::new(&out_dir).join("bindings.rs");

    bindings
        .write_to_file(out_path)
        .expect("Couldn't write bindings!");
}
