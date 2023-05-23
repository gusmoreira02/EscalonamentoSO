/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "task.h"
#include "list.h"
#include "CPU.h"
#include "schedule_rr.h"

#define SIZE    100




int main(int argc, char *argv[])
{
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    clock_t tempo;
    tempo = clock();
    testRR(fopen("rr-schedule.txt","r"), temp, task, name, priority, burst);
    tempo = clock() - tempo;
    double timeRR = ((double)tempo)/CLOCKS_PER_SEC;
    printf("\n O Round-Robin levou %f  \n", timeRR);
    //fclose("rr-schedule.txt");




    testFCFS(fopen("rr-schedule.txt","r"), temp, task, name, burst);
    tempo = clock() - tempo;
    double timefcfs = ((double)tempo)/CLOCKS_PER_SEC;
    printf("\n O FCFS levou %f segundos \n", timefcfs);
    //fclose("rr-schedule.txt");


    testRRP(fopen(argv[1], "r"), temp, task, name, priority, burst);
    tempo = clock() - tempo;
    double timerrp = ((double)tempo) / CLOCKS_PER_SEC;
    printf("\n O prioridade levou %f segundos \n", timerrp);
    //fclose("rr-schedule.txt");
    return 0;
}


void testRR(FILE* in, char* task, char* name, int priority, int burst) {
    printf("\nROUND ROBIN: \n");
    char *temp = NULL; // Inicializar a variável 'temp' como NULL

    while (fgets(task, SIZE, in) != NULL) {
        free(temp); // Liberar a memória anteriormente alocada em 'temp'
        temp = strdup(task);
        name = strtok(temp, ",");
        priority = atoi(strtok(NULL, ",")); // Usar NULL como primeiro argumento para continuar a tokenização a partir de 'temp'
        burst = atoi(strtok(NULL, ","));

        addRR(name, priority, burst);
    }

    free(temp); // Liberar a memória alocada em 'temp'
    fclose(in);

    scheduleRR();
}
void testFCFS(FILE* in, char* temp, char* task, char* name, int burst){
    printf("\n ESCALONADOR FCFS: \n");
    while (fgets(task, SIZE, in) != NULL) {
        temp = strdup(task);
        name = strtok(temp, ",");
       // priority = atoi(strtok(NULL, ",")); // Usar NULL como primeiro argumento para continuar a tokenização a partir de 'temp'
        burst = atoi(strtok(NULL, ","));

        free(temp);
    }

    fclose(in);

    scheduleFCFS();
}

void testRRP(FILE* in, char* temp, char* task, char* name, int priority, int burst) {
    printf("\n ESCALONADOR ROUND ROBIN P: \n");
    while (fgets(task, SIZE, in) != NULL) {
        temp = strdup(task);
        name = strtok(&temp, ",");
        priority = atoi(strtok(&temp, ","));
        burst = atoi(strtok(&temp, ","));
        addRRP(name, priority, burst);

        free(temp);
    }

    fclose(in);

    scheduleRRP();
}


