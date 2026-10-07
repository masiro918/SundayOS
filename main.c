#include "include/kstdio.h"
#include "include/system.h"

void sys_initializer() {
    /* Irroittavaa moniajoa ei käytetä batch-mallissa. */
    printk("Set timer interrupts...");
    timer_initalizer();
    printk("Start init...");
    run_init();
}

void init() {
    sys_initializer();
    while (1) {
        
    }
}