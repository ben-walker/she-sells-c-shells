#ifndef PROCESS_LIST_
#define PROCESS_LIST_

#include <stdbool.h>
#include <sys/types.h>

typedef enum procState {
    Open,
    Closed
} procState;

typedef struct PCB {
    pid_t pid;
    bool background;
    struct PCB *next;
    procState state;
} PCB;

void trackProcess(const pid_t pid, bool background);

void removeProcess(const pid_t pid);

void closeProcess(const pid_t pid);

PCB *getFirstClosedProcess();

void procPeek();

void destroyProcList();

#endif // PROCESS_LIST_
