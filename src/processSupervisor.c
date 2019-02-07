/**
 * Ben Walker
 * CIS*3110
 * 
 * A library to watch over and manage processes;
 * perform child/parent processes, in the foreground or background,
 * and cleanup when processes close.
 */

#include "processSupervisor.h"
#include "argsHandler.h"
#include "internal.h"
#include "external.h"
#include "processList.h"
#include <stdio.h>
#include <sys/wait.h>

/**
 * sigChildHandler()
 * This function should be assigned to the SIGCHLD signal.
 * Wait for the pid to end, mark that process as closed.
 */
void sigChildHandler(int signo, siginfo_t *si, void *data) {
    if (waitpid(si->si_pid, NULL, 0) != -1)
        closeProcess(si->si_pid);
}

/**
 * checkForClosedProc()
 * Iterate through all closed processes, display if background,
 * then remove that process from the list of processes.
 */
void checkForClosedProc() {
    PCB *closedProc;
    while ((closedProc = getFirstClosedProcess()) != NULL) {
        if (closedProc->background)
            printf("[%d] -> done\n", closedProc->pid);
        removeProcess(closedProc->pid); // closed process is removed from the list
    }
}

/**
 * child()
 * Responsible for deciding if a command is internal/external and
 * running it as such.
 */
void child(char **argv) {
    char **cleanArgs = consumeSpecialArgs(argv);
    isInternal(argv[0]) ? runInternal(cleanArgs) : runExternal(cleanArgs);
    freeArgs(cleanArgs);
}

/**
 * foreground()
 * Add process to list, wait for it to end
 */
void foreground(pid_t childPid) {
    trackProcess(childPid, false);
    waitpid(childPid, NULL, 0);
}

/**
 * background()
 * Add process to list, don't wait for it to end
 */
void background(pid_t childPid) {
    trackProcess(childPid, true);
    printf("[%d] -> background\n", childPid);
}

/**
 * parent()
 * Determine if child command is background or foreground,
 * act appropriately.
 */
void parent(pid_t childPid, char **argv) {
    if (!isBackground(argv)) {
        foreground(childPid);
        return;
    }
    background(childPid);
}
