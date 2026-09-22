#include "types.h"

struct task_context {
	uint32_t ra;
	uint32_t sp;
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
};

#define MAX_TASK 8
#define STACK_SIZE 1024

#define PROGRAM_LOAD_BASE 0x18000
#define PROGRAM_LOAD_STEP 0x10000

extern int task_count;
extern struct task_context tasks[MAX_TASK];
extern struct task_context *active_task;
extern struct task_context kernel;


extern void do_context_switch(struct task_context *old, struct task_context *new);
extern uint32_t reserve_program_load_addr();
