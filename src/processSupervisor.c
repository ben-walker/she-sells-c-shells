#include "processSupervisor.h"
#include "argsHandler.h"
#include "internal.h"
#include "external.h"
#include "processList.h"
#include <stdio.h>
#include <sys/wait.h>

static volatile sig_atomic_t closedPid = 0;

void sigChildHandler(int signo, siginfo_t *si, void *data) {
    if (waitpid(si->si_pid, NULL, 0) != -1) {
        closedPid = si->si_pid;
    }
}

void checkForClosedProc() {
    if (closedPid != 0) {
        if (isProcBackground(closedPid))
            printf("[%d] -> done\n", closedPid);
        closedPid = 0;
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
