#ifndef PROCESS_LIST_
#define PROCESS_LIST_

#include <stdbool.h>
#include <sys/types.h>

typedef struct PCB {
    pid_t pid;
    bool background;
    struct PCB *next;
} PCB;

PCB *createProcList(const pid_t pid, bool background);

int trackProcess(const pid_t pid, bool background, PCB *head);

void removeProcess(const pid_t pid, PCB **head);

bool isProcBackground(const pid_t pid, PCB *head);

void procPeek(PCB *head);

void destroyProcList(PCB *head);

#endif // PROCESS_LIST_
