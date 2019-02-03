#include "processSupervisor.h"
#include "internal.h"
#include "external.h"
#include <stdio.h>

void child(pid_t pid, char **argv) {
    isInternal(argv[0]) ? runInternal(argv) : runExternal(argv);
}

void parent(pid_t childPid, char **argv) {
    wait(NULL);
}
