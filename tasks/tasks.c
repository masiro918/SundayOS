#include "../include/types.h"
#include "../include/stdlib.h"
#include "../include/kstdio.h"
#include "../include/mm.h"

extern struct task_context *active_task;

/**
 * @brief Loads program by filename into specific address and executes it.
 * 
 * @param filename the program's filename
 * @param load_addr address to load
 */
void load_and_execute_program_at(const char *filename, uint32_t load_addr) {
	register uint32_t op asm("a0") = 3;
	register const char *file asm("a1") = filename;
	register uint32_t addr asm("a2") = load_addr;

	asm volatile(
		"ecall"
		: "+r"(op)
		: "r"(file), "r"(addr)
		: "memory"
	);
}

void run_init() {
	static const char filename_control[] = "control.bin";
	uint32_t load_addr = reserve_program_load_addr();
	int pid = task_create((void (*)(void))load_addr);

	if (pid < 0) {
		printk("Failed to create task");
		return;
	}

	printk("Created control task, starting batch execution");
	active_task = &tasks[pid];
	load_and_execute_program_at(filename_control, load_addr);
}