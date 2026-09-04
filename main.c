#include "include/kstdio.h"
#include "include/system.h"

void sys_initializer() {
    timer_initalizer();
    build_tasks();
}

void init() {
    sys_initializer();
    printk("Moving to userland...\n");
    schedule();
}