#ifndef PROCESS_SUPERVISOR_
#define PROCESS_SUPERVISOR_

#include "processList.h"
#include <stdlib.h>
#include <sys/types.h>

void sigChildHandler();

void checkForClosedProc();

void child(pid_t pid, char **argv);

void parent(pid_t childPid, char **argv, PCB *procs);

#endif // PROCESS_SUPERVISOR_
