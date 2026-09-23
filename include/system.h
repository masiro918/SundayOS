#include "types.h"

extern uint32_t next_free_program_load_addr;

extern uint32_t reserve_program_load_addr();
extern void load_and_execute_program_at(const char *filename, uint32_t load_addr);

extern void run_init();
extern void schedule();
extern void timer_initalizer();
