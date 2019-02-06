/**
 * Ben Walker
 * CIS*3110
 * 
 * The main command loop for the shell.
 * Set up a signal handler for SIGCHLD signals,
 * get the next user command in a loop,
 * fork() to run/wait for the command,
 * cleanup memory when the user exits.
 */

#include "shell.h"
#include "prompt.h"
#include "processSupervisor.h"
#include "argsHandler.h"
#include "processList.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

/**
 * shellCleanup()
 * Call library functions to release allocated memory
 */
void shellCleanup(Prompt *prompt, char **argv) {
    destroy(prompt);
    freeArgs(argv);
    destroyProcList(); // process list is static, don't need to pass anything
}

/**
 * sigHandlerSetup()
 * Associate function with the SIGCHLD signal
 */
void sigHandlerSetup() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO // SA_SIGINFO - add siginfo_t argument to signal handler
        | SA_RESTART; // SA_RESTART - system calls restartable across signals
    sa.sa_sigaction = sigChildHandler;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

/**
 * commandLoop()
 * Get user arguments and fork to process child/parent
 */
void commandLoop(Prompt *prompt) {
    char **argv;

    while (true) {
        checkForClosedProc(); // display any background processes that closed since last iteration
        getArgs(prompt->comm, &argv);
        if (isBlank(argv)) continue;
        if (isInternalExit(argv)) break;

        pid_t pid = fork();
        switch (pid) {
            case -1: perror("fork");
            case 0: child(pid, argv);
            default: parent(pid, argv);
        }
        update(prompt); // if the user somehow switched to root, this will reflect that change
    }
    shellCleanup(prompt, argv);
}

/**
 * boot()
 * Called by main; sets up SIGCHLD handler/prompt, starts command loop
 */
void boot() {
    sigHandlerSetup();
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}
