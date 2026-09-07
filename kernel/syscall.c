#include "../include/interrupts.h"
#include "../include/kstdio.h"
#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/system.h"
#include "../include/mm.h"

extern uint8_t peek(uint32_t addr);
extern void poke(uint32_t addr, int val);
extern void run_task(int pid);

static uint32_t read_saved_mepc() {
    uint32_t mepc = 0;
    mepc |= (uint32_t)peek(0x1FFFFB);
    mepc |= ((uint32_t)peek(0x1FFFFC)) << 8;
    mepc |= ((uint32_t)peek(0x1FFFFD)) << 16;
    mepc |= ((uint32_t)peek(0x1FFFFE)) << 24;
    return mepc;
}

static void save_current_task_context(int pid) {
    if (pid < 0 || pid >= task_count) {
        printk("PID is less than 0!");
        return;
    }

    uint32_t saved_sp;
    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t s8;
    uint32_t s9;
    uint32_t s10;
    uint32_t s11;

    asm volatile("mv %0, t6" : "=r"(saved_sp));

    asm volatile(
        "mv %0, s0\n"
        "mv %1, s1\n"
        "mv %2, s2\n"
        "mv %3, s3\n"
        "mv %4, s4\n"
        "mv %5, s5\n"
        "mv %6, s6\n"
        "mv %7, s7\n"
        "mv %8, s8\n"
        "mv %9, s9\n"
        "mv %10, s10\n"
        "mv %11, s11"
        : "=r"(s0), "=r"(s1), "=r"(s2), "=r"(s3), "=r"(s4), "=r"(s5),
          "=r"(s6), "=r"(s7), "=r"(s8), "=r"(s9), "=r"(s10), "=r"(s11)
        :
        :
    );

    tasks[pid].ra = read_saved_mepc();
    tasks[pid].sp = saved_sp;
    tasks[pid].s0 = s0;
    tasks[pid].s1 = s1;
    tasks[pid].s2 = s2;
    tasks[pid].s3 = s3;
    tasks[pid].s4 = s4;
    tasks[pid].s5 = s5;
    tasks[pid].s6 = s6;
    tasks[pid].s7 = s7;
    tasks[pid].s8 = s8;
    tasks[pid].s9 = s9;
    tasks[pid].s10 = s10;
    tasks[pid].s11 = s11;
}

static int get_active_pid() {
    if (!active_task) {
        return -1;
    }

    for (int pid = 0; pid < task_count; pid++) {
        if (&tasks[pid] == active_task) {
            return pid;
        }
    }

    return -1;
}

void syscall_handler(int param1, int param2, int param3, int param4, int param5, int param6, int param7, int num) {
    int current_pid = get_active_pid();
    printf("[pid:%d] syscall: %d\n", current_pid, num);
    char *output = (char *)param1;
    (void)param2;
    (void)param3;
    (void)param4;
    (void)param5;
    (void)param6;
    (void)param7;
    
    switch (num)
    {
        case 1:
            /* write test */
            printf("Test: Hello world!\n");
            break;

        case 2:
            /* write string */
            printf("%s", output);            
            break;

        case 11: {
            /* batch spawn: luo task-tietue ennen latausta ja suorita heti */
            char *filename = (char *)param1;
            if (filename) {
                /* save current context before jumping to spawned task */
                int current_pid = get_active_pid();
                save_current_task_context(current_pid);

                uint32_t load_addr = reserve_program_load_addr();
                int pid = task_create((void (*)(void))load_addr);

                if (pid < 0) {
                    printk("Batch spawn failed: no free task slots");
                    break;
                }

                active_task = &tasks[pid];
                load_and_execute_program_at(filename, load_addr);
            }
            break;
        }

        case 12:
            /* kill: param1 = pid */
            kill_task(param1);
            break;

        case 13:
            /* sleep: TODO */
            break;

        case 14: {
            /* exit: opposite of spawn (11), return to previous task context */
            int pid = get_active_pid();

            if (pid < 0) {
                pid = task_count - 1;
            }

            if (pid < 0) {
                printk("Exit failed: no task to terminate");
                break;
            }

            int previous_pid = pid - 1;

            uint32_t mepc = tasks[previous_pid].ra;
            poke(0x1FFFFB, mepc);

            if (previous_pid >= 0) {
                active_task = &tasks[previous_pid];
                run_task(previous_pid);
            } else {
                active_task = &kernel;
            }
            break;
        }

        default:
            printf("Unkown syscall num %d", num);
            break;
    }
}