#include "processList.h"
#include <stdlib.h>
#include <stdio.h>

PCB *createProcList(const pid_t pid, bool background) {
    PCB *procs = malloc(sizeof(PCB));
    procs->pid = pid;
    procs->background = background;
    procs->next = NULL;
    return procs;
}

int trackProcess(const pid_t pid, bool background, PCB *head) {
    if (head == NULL)
        return -1;
    PCB *current = head;
    while (current->next != NULL)
        current = current->next;

    current->next = malloc(sizeof(PCB));
    current->next->pid = pid;
    current->next->background = background;
    current->next->next = NULL;
    return 0;
}

void removeProcess(const pid_t pid, PCB **head) {
    PCB *current, *previous = NULL;

    for (current = *head; current != NULL; previous = current, current = current->next) {
        if (current->pid == pid) {
            if (previous == NULL)
                *head = current->next;
            else
                previous->next = current->next;
            free(current);
            return;
        }
    }
}

bool isProcBackground(const pid_t pid, PCB *head) {
    PCB *current = head;
    while (current != NULL) {
        if (current->pid == pid)
            return current->background;
        current = current->next;
    }
    return false;
}

void procPeek(PCB *head) {
    PCB *current = head;
    printf("Processes:\n");
    while (current != NULL) {
        const char *status = current->background ? "background" : "foreground";
        printf("  [%d] -> %s\n", current->pid, status);
        current = current->next;
    }
}

void destroyProcList(PCB *head) {
    PCB *current = head, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}
