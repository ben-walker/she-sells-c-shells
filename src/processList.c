/**
 * Ben Walker
 * CIS*3110
 * 
 * A library to maintain a linked list of active processes and
 * their current state (Open or Closed).
 */

#include "processList.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * The PCB list is static because it needs to be acted on
 * from within the SIGCHLD handler, and unfortunately it's impossible
 * to pass data to these handlers.
 * 
 * Acts as stateful PCB list for the entire shell.
 */
static PCB *procs = NULL;

/**
 * createProcList()
 * Creates the first element of the PCB list
 */
void createProcList(const pid_t pid, bool background) {
    procs = malloc(sizeof(PCB));
    procs->pid = pid;
    procs->background = background;
    procs->state = Open;
    procs->next = NULL;
}

/**
 * trackProcess()
 * Add a process to the end of the PCB list with Open state
 */
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

/**
 * removeProcess()
 * Remove process from PCB list with matching pid.
 */
void removeProcess(const pid_t pid) {
    PCB *current, *previous = NULL;

    // track previous PCB as it will replace the one we remove
    for (current = procs; current != NULL; previous = current, current = current->next) {
        if (current->pid == pid) {
            if (previous == NULL) // remove the first element
                procs = current->next;
            else // leapfrog the current element (omit it from the list)
                previous->next = current->next;
            free(current);
            return;
        }
    }
}

/**
 * closeProcess()
 * Mark a PCB with matching pid as Closed
 */
void closeProcess(const pid_t pid) {
    PCB *current = procs;
    while (current != NULL) {
        if (current->pid == pid) {
            current->state = Closed;
            return;
        }
        current = current->next;
    }
}

/**
 * getFirstClosedProcess()
 * Return pointer to the first process with Closed state or NULL
 */
PCB *getFirstClosedProcess() {
    PCB *current = procs;
    while (current != NULL) {
        if (current->state == Closed)
            return current;
        current = current->next;
    }
    return NULL;
}

/**
 * procPeek()
 * Print out processes currently in the PCB list and their background status
 */
void procPeek() {
    PCB *current = procs;
    printf("Processes:\n");
    while (current != NULL) {
        const char *status = current->background ? "background" : "foreground";
        printf("  [%d] -> %s\n", current->pid, status);
        current = current->next;
    }
}

/**
 * destroyProcList()
 * Release all memory from the PCB list
 */
void destroyProcList() {
    PCB *current = procs, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    procs = NULL;
}
