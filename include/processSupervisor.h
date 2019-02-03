#ifndef PROCESS_SUPERVISOR_
#define PROCESS_SUPERVISOR_

#include <stdlib.h>

void sigChildHandler();

void child(pid_t pid, char **argv);

void parent(pid_t childPid, char **argv);

#endif // PROCESS_SUPERVISOR_
