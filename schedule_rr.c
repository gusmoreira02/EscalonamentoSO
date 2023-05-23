#include "schedule_rr.h"
#include "task.h"
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "CPU.h"
///////////////////////////////////////////////

static struct node* RR = NULL;


// Adiciona uma tarefa à lista
void addRR(char* name, int priority, int burst) {
    Task* taskRR = malloc(sizeof(Task));
    taskRR->name = malloc(strlen(name) + 1);
    strcpy(taskRR->name, name);
    taskRR->priority = priority;
    taskRR->burst = burst;
    append(&RR, taskRR);
}

Task* nextask() {
    if (!RR)
        return NULL;

    Task* taskRR = RR->task;
    RR = RR->next;

    return taskRR;
}

// Chama o escalonador
void scheduleRR() {
    Task* taskRR;

    while ((taskRR = nextask())) {
        if (taskRR->burst <= QUANTUM && taskRR->burst > 0) {
            run(taskRR, taskRR->burst);
        } else if (taskRR->burst > 0) {
            run(taskRR, QUANTUM);
            addRR(taskRR->name, taskRR->priority, taskRR->burst - QUANTUM);
        }
    }
}

/////////////////////////////

static struct node *FCFS = NULL;

void addFCFS(char *name, int burst){
    Task* taskFCFS = malloc(sizeof(Task));
    taskFCFS->name = name;
    taskFCFS->burst = burst;
    insert(&RR, taskFCFS);
}
void scheduleFCFS() {
    while (FCFS != NULL) {
        struct node* temp = FCFS;
        Task* taskFCFS = temp->task;

        run(taskFCFS, taskFCFS->burst);

        FCFS = FCFS->next;

        free(taskFCFS->name);
        free(taskFCFS);
        free(temp);
    }
}
/////////////////////////////

static struct node *taskLists[MAX_PRIORITY];

void addRRP(char *name, int priority, int burst) {
    Task* taskRR = malloc(sizeof(Task));
    taskRR->name = name;
    taskRR->priority = priority;
    taskRR->burst = burst;
    insert(&taskLists[priority - 1], taskRR);
}

Task* nextTask() {
    for (int i = 0; i < MAX_PRIORITY; i++) {
        if (taskLists[i] != NULL) {
            Task* taskRR = taskLists[i]->task;
            taskLists[i] = taskLists[i]->next;
            return taskRR;
        }
    }
    return NULL;
}

void scheduleRRP() {
    while (1) {
        Task* taskRR = nextTask();
        if (taskRR == NULL)
            break;

        if (taskRR->burst <= QUANTUM) {
            run(taskRR, taskRR->burst);
            free(taskRR->name);
            free(taskRR);
        } else {
            run(taskRR, QUANTUM);
            taskRR->burst -= QUANTUM;
            addRRP(taskRR->name, taskRR->priority, taskRR->burst);
            free(taskRR);
        }
    }
}


