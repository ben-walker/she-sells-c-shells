#include "processSupervisor.h"
#include "argsHandler.h"
#include "internal.h"
#include "external.h"
#include "processList.h"
#include <stdio.h>
#include <sys/wait.h>

void sigChildHandler(int signo, siginfo_t *si, void *data) {
    if (waitpid(si->si_pid, NULL, 0) != -1)
        closeProcess(si->si_pid);
}

void checkForClosedProc() {
    PCB *closedProc;
    while ((closedProc = getFirstClosedProcess()) != NULL) {
        if (closedProc->background)
            printf("[%d] -> done\n", closedProc->pid);
        removeProcess(closedProc->pid);
    }
}

void child(pid_t pid, char **argv) {
    isInternal(argv[0]) ? runInternal(argv) : runExternal(argv);
}

void foreground(pid_t childPid) {
    trackProcess(childPid, false);
    waitpid(childPid, NULL, 0);
}

void background(pid_t childPid) {
    trackProcess(childPid, true);
    printf("[%d] -> background\n", childPid);
}

void parent(pid_t childPid, char **argv) {
    if (!isBackground(argv)) {
        foreground(childPid);
        return;
    }
    background(childPid);
}
