/**
 * Various list operations
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"


// add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
    // Create a new node for the new task
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;
    newNode->next = NULL;

    // If the list is empty, make the new node as the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Find the last node in the list
    struct node *lastNode = *head;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }

    // Append the new node at the end of the list
    lastNode->next = newNode;
}


// delete the selected task from the list
void delete(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}


void append(struct node **RR, Task *escalonTarefa){
    struct node *aux;

    aux = *RR;


    if(aux == NULL) {
        insert(RR, escalonTarefa);
    return;
    }

    while(aux->next !=NULL) aux = aux->next;

    struct node* no = malloc(sizeof(struct node));

    no->task = escalonTarefa;
    no->next = NULL;
    aux->next = no;

}
