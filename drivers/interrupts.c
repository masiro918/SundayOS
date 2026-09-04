#include "../include/types.h"
#include "../include/interrupts.h"
#include "../include/kstdio.h"

volatile int run_scheduler = 0;

void interrupt_handler() {
    timer_handler();

    // Request task switch.
    run_scheduler = 1;
}

void timer_initalizer() {
    init_machine_timer_interrupt();
    enable_interrupts();
}