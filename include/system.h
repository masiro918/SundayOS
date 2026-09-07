#include "types.h"

extern uint32_t next_free_program_load_addr;

extern uint32_t reserve_program_load_addr();
extern uint32_t get_next_program_load_addr();
extern void reset_program_load_addr();
extern void load_and_execute_program_at(const char *filename, uint32_t load_addr);
extern uint32_t load_and_execute_program_from_db(const char *filename);

extern void build_tasks();
extern void schedule();
extern void timer_initalizer();
