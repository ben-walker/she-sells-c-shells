#include "processSupervisor.h"
#include "argsHandler.h"
#include "internal.h"
#include "external.h"
#include <stdio.h>
#include <sys/wait.h>

static volatile sig_atomic_t closedPid = 0;

void sigChildHandler(int signo, siginfo_t *si, void *data) {
    if (waitpid(si->si_pid, NULL, 0) != -1) {
        closedPid = si->si_pid;
    }
}

void checkForClosedProc(PCB *procs) {
    if (closedPid != 0) {
        if (isProcBackground(closedPid, procs))
            printf("[%d] -> done\n", closedPid);
        removeProcess(closedPid, &procs);
        closedPid = 0;
    }
}

void child(pid_t pid, char **argv) {
    isInternal(argv[0]) ? runInternal(argv) : runExternal(argv);
}

void foreground(pid_t childPid, PCB *procs) {
    trackProcess(childPid, false, procs);
    waitpid(childPid, NULL, 0);
}

void background(pid_t childPid, PCB *procs) {
    trackProcess(childPid, true, procs);
    printf("[%d] -> background\n", childPid);
}

void parent(pid_t childPid, char **argv, PCB *procs) {
    if (!isBackground(argv)) {
        foreground(childPid, procs);
        return;
    }
    background(childPid, procs);
}
