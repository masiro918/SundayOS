extern void kill_task(int pid);
extern void checkpoint();
extern int task_create(void (*task)(void));