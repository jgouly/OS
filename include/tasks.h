#ifndef TASKS_H
#define TASKS_H

#include "pit.h"
#include "kio.h"
#include "vmm.h"

extern void tss_flush();

static char TASK_EMPTY =0;
static char TASK_READY =1;
 
 typedef struct TaskType {
	unsigned int PID;
	unsigned int stack;
	unsigned char status;
} TaskType;

static unsigned int tss[32] = { 0, 0, 0x10 };

typedef struct cpu_state {
    // Von Hand gesicerte Register
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int esi;
    unsigned int edi;
    unsigned int ebp;
 
    unsigned int intr;
    unsigned int error;
 
    // Von der CPU gesichert
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
    unsigned int esp;
    unsigned int ss;
} cpu_state;

static TaskType Tasks[100];
static unsigned int AllTasks;
static unsigned int currentPID;

unsigned int* dec(unsigned int* tPtr);
void init_tasks();
void task_create (unsigned char priority, unsigned long* address,bool cli);
void switch_to_user_mode();

#endif