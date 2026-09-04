#include "../include/stdio.h"
#include "../include/stdlib.h"


void task1(void) {
begin_2:
	puts("Task1: Created!\n");
	int i = 0;
	while (1) {
		i = i + 1;
		printf("one \n");
		printf("two \n");
		printf("three \n");
		printf("i is %d \n", i);
		checkpoint();
	}
}

void task2(void) {
	int i = 0;
begin_3:
	while (i < 10) {
		printf("%d. Hello world!\n", i);
		i++;
		checkpoint();
	}
	i = 0;
	kill_task(1);
	checkpoint();
	goto begin_3;
}

void task0(void) {
begin_1:
	puts("Task0: Created!\n");
	int i = 0;
	int j = 0;
	while (i < 10) {
		printf("enter into loop\n");
		while (j < 20) {
			j = j + 1;
			printf("j is %d \n", j);
			checkpoint();
		}
		
		i = i + 1;
		printf("i is %d \n", i);
		checkpoint();
	}
	task_create(&task2);
	goto begin_1;
}

void build_tasks() {
	task_create(&task0);
	task_create(&task1);
}