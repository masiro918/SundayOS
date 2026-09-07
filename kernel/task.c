#include "../include/mm.h"
#include "../include/kstdio.h"

struct task_context tasks[MAX_TASK];
struct task_context *active_task;
struct task_context kernel;

/**
 * @brief Force kill task for pid `id`.
 * 
 * @param i `pid` identifier
 */
void kill_task(int pid) {
	if (pid < 0 || pid >= task_count) {
		return;
	}

	printk("Killing task\n");
	tasks[pid].ra = (uint32_t)-1;
	tasks[pid].sp = (uint32_t)-1;
}

/**
 * @brief switch to task `task[i]`
 * 
 * @param i index in array task
 */
 
void run_task(int pid) {
	if (pid < 0 || pid >= task_count) {
		return;
	}

	if (tasks[pid].ra == (uint32_t)-1) {
		printk("The task is killed\n");
		tasks[pid].ra = (uint32_t)-2;
		return;
	}

	if (tasks[pid].ra == (uint32_t)-2) {
		return;
	}

	active_task = &tasks[pid];
	printk("Run task");
	do_context_switch(&kernel, &tasks[pid]);
}

/**
 * Swaps active_task and kernel.
 */
void to_kernel() {
	struct task_context *_active_task = active_task;
	active_task = &kernel;
	do_context_switch(_active_task, &kernel);
}