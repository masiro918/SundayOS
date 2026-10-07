#include "../include/types.h"
#include "../include/interrupts.h"
#include "../include/kstdio.h"

volatile int run_scheduler = 1;

void interrupt_handler() {
    timer_handler();

    if (run_scheduler == 0)
        printk("Interrupt during process");
        return;

    //TODO: if pressing ctrl+c, force kill the current process

    // Request task switch.
    run_scheduler = 1;
}

void timer_initalizer() {
    init_machine_timer_interrupt();
    enable_interrupts();
}