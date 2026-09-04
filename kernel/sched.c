#include "../include/mm.h"

extern void run_task(int pid);

/**
 * @brief The heart of os <3. basic round-robin scheduling
 * 
 */
void schedule() {
	int pid = 0;
	while (1) {
		run_task(pid);
		pid = (pid + 1) % task_count;
	}
}