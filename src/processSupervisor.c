#include "processSupervisor.h"
#include "argsHandler.h"
#include "internal.h"
#include "external.h"
#include <stdio.h>

void sigChildHandler() {
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) != -1) {
        waitpid(pid, NULL, 0);
    }
}

void child(pid_t pid, char **argv) {
    isInternal(argv[0]) ? runInternal(argv) : runExternal(argv);
}

void foreground(pid_t childPid) {
    wait(NULL);
}

void background(pid_t childPid) {
    return;
}

void parent(pid_t childPid, char **argv) {
    if (!isBackground(argv)) {
        foreground(childPid);
        return;
    }
    background(childPid);
}
