#if defined(RUST_ZEPHYR_BUILD_BRIDGE)
struct _reent;
#endif

#include "autoconf.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>

#if !defined(CONFIG_CPP) || CONFIG_CPP == 0
#error "The Zephyr project must be configured to support C++"
#endif