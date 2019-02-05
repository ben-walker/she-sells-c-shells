#include "processSupervisor.h"
#include "argsHandler.h"
#include "internal.h"
#include "external.h"
#include <stdio.h>
#include <sys/wait.h>

volatile sig_atomic_t closedPid = 0;

void sigChildHandler(int signo, siginfo_t *si, void *data) {
    if (waitpid(si->si_pid, NULL, 0) != -1)
        closedPid = si->si_pid;
}

void child(pid_t pid, char **argv) {
    isInternal(argv[0]) ? runInternal(argv) : runExternal(argv);
}

void foreground(pid_t childPid) {
    waitpid(childPid, NULL, 0);
}

void background(pid_t childPid) {
    printf("[%d] -> background\n", childPid);
}

void parent(pid_t childPid, char **argv) {
    if (!isBackground(argv)) {
        foreground(childPid);
        return;
    }
    background(childPid);
}
