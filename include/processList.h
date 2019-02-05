#ifndef PROCESS_LIST_
#define PROCESS_LIST_

#include <stdbool.h>
#include <sys/types.h>

typedef struct PCB {
    pid_t pid;
    bool background;
    struct PCB *next;
} PCB;

void trackProcess(const pid_t pid, bool background);

void removeProcess(const pid_t pid);

bool isProcBackground(const pid_t pid);

void procPeek();

#endif // PROCESS_LIST_
