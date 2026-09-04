extern int run_scheduler;
extern void to_kernel();

void checkpoint() {
	if (run_scheduler) {
		run_scheduler = 0;
		to_kernel();
	}
}