#include "include/kstdio.h"
#include "include/system.h"

void sys_initializer() {
    /* Irroittavaa moniajoa ei käytetä batch-mallissa. */
    build_tasks();
}

void init() {
    sys_initializer();
    printk("Batch tasks completed, entering idle loop");

    while (1) {
    }
}