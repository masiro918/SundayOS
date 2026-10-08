#include "../include/types.h"
#include "../include/interrupts.h"
#include "../include/keyboard.h"
#include "../include/kstdio.h"

volatile int run_scheduler = 1;

void interrupt_handler() {
    timer_handler();

    if (run_scheduler == 0) {
        uint32_t key = key_pressed();

        if (key == 1) {
            printk("Force kill the process ");
            exit_current_task();
        }
        return;
    }

    // Request task switch.
    run_scheduler = 1;
}

void timer_initalizer() {
    init_machine_timer_interrupt();
    enable_interrupts();
}