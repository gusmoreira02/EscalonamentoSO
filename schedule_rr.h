#define MIN_PRIORITY 1
#define MAX_PRIORITY 10
#include "task.h"
#include <stdio.h>
// add a task to the list
void addRR(char *name, int priority, int burst);

//void testRR(FILE* in, char* temp, char* task, char* name, int priority, int burst);
Task *nextask();
void scheduleRR();
// invoke the scheduler
