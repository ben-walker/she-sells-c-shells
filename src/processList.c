#include "processList.h"
#include <stdlib.h>
#include <stdio.h>

static PCB *procs = NULL;

void createProcList(const pid_t pid, bool background) {
    procs = malloc(sizeof(PCB));
    procs->pid = pid;
    procs->background = background;
    procs->state = Open;
    procs->next = NULL;
}

void trackProcess(const pid_t pid, bool background) {
    if (procs == NULL) {
        createProcList(pid, background);
        return;
    }
    PCB *current = procs;
    while (current->next != NULL)
        current = current->next;

    current->next = malloc(sizeof(PCB));
    current->next->pid = pid;
    current->next->background = background;
    current->next->state = Open;
    current->next->next = NULL;
}

void removeProcess(const pid_t pid) {
    PCB *current, *previous = NULL;

    for (current = procs; current != NULL; previous = current, current = current->next) {
        if (current->pid == pid) {
            if (previous == NULL)
                procs = current->next;
            else
                previous->next = current->next;
            free(current);
            return;
        }
    }
}

bool isProcBackground(const pid_t pid) {
    PCB *current = procs;
    while (current != NULL) {
        if (current->pid == pid)
            return current->background;
        current = current->next;
    }
    return false;
}

void procPeek() {
    PCB *current = procs;
    printf("Processes:\n");
    while (current != NULL) {
        const char *status = current->background ? "background" : "foreground";
        printf("  [%d] -> %s\n", current->pid, status);
        current = current->next;
    }
}

void destroyProcList() {
    PCB *current = procs, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    procs = NULL;
}
