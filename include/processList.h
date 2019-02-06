/**
 * Ben Walker
 * CIS*3110
 * 
 * A library to maintain a linked list of active processes and
 * their current state (Open or Closed).
 */

#ifndef PROCESS_LIST_
#define PROCESS_LIST_

#include <stdbool.h>
#include <sys/types.h>

/**
 * enum procState
 * Enumerates process states (Open or Closed)
 */
typedef enum procState {
    Open, // process is running
    Closed // process is completed
} procState;

/**
 * struct PCB
 * "Process Control Block" - holds data regarding a process
 */
typedef struct PCB {
    pid_t pid; // the id of the process
    bool background; // whether it's background or not
    struct PCB *next; // next process in the list
    procState state; // Open or Closed (see above)
} PCB;

void trackProcess(const pid_t pid, bool background);

void removeProcess(const pid_t pid);

void closeProcess(const pid_t pid);

PCB *getFirstClosedProcess();

void procPeek();

void destroyProcList();

#endif // PROCESS_LIST_
