#include "../include/types.h"
#include "../include/mm.h"

int task_count = 0;

// stack of a single task
uint8_t task_stack[MAX_TASK][STACK_SIZE];

/**
 * @brief create task
 * 
 * @param task startpoint of the task
 * @return int created pid
 */
int task_create(void (*task)(void)) {
	if (task_count >= MAX_TASK) {
		return -1;
	}

	int pid = task_count++;
	tasks[pid].ra = (uint32_t) task;
	tasks[pid].sp = (uint32_t) &task_stack[pid][STACK_SIZE - 1];
	return pid;
}