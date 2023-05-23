#include "schedule_rr.h"
#include "task.h"
#include  <string.h>
#include <stdlib.h>
#include "list.h"
#include "CPU.h"


static struct node *cabecalho = NULL;

// add a task to the list 
void addSFJ(char *name, int priority, int burst){
   Task* taskSJF = malloc(sizeof(Task));
   taskSJF->name = (char*)malloc(strlen(name));
   strcpy(taskSJF->name,name);
   taskSJF->priority = priority;
   taskSJF->burst = burst;
   insert(&cabecalho, taskSJF);

}
// invoke the scheduler

Task *proxTaskSJF(){
   if(!cabecalho) return NULL;

   Task* taskSJF = cabecalho->task;
   struct node *nodeSJF = cabecalho->next;

   while(nodeSJF){
       if(taskSJF->burst > nodeSJF->task->burst){ //se o tempo de burst for menor
           taskSJF = nodeSJF->task;
       }
       nodeSJF = nodeSJF->next;
   }
   delete(&cabecalho, taskSJF);

   return taskSJF;

}


void scheduleSJF(){
   Task* taskSJF;


   while(taskSJF = proxTaskSJF()){
      run(taskSJF, taskSJF->burst);
   }
}
