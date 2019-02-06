/**
 * Ben Walker
 * CIS*3110
 * 
 * A library to watch over and manage processes;
 * perform child/parent processes, in the foreground or background,
 * and cleanup when processes close.
 */

#ifndef PROCESS_SUPERVISOR_
#define PROCESS_SUPERVISOR_

#include <stdlib.h>
#include <sys/types.h>

void sigChildHandler();

void checkForClosedProc();

void child(char **argv);

void parent(pid_t childPid, char **argv);

#endif // PROCESS_SUPERVISOR_
