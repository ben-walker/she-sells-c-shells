#include "shell.h"
#include "prompt.h"
#include "processSupervisor.h"
#include "argsHandler.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

void shellCleanup(Prompt *prompt, char **argv) {
    destroy(prompt);
    freeArgs(argv);
}

void sigHandlerSetup() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sa.sa_sigaction = sigChildHandler;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

void commandLoop(Prompt *prompt) {
    char **argv;

    while (true) {
        getArgs(prompt->comm, &argv);
        if (isBlank(argv)) continue;
        if (isInternalExit(argv)) break;

        pid_t pid = fork();
        switch (pid) {
            case -1: perror("fork");
            case 0: child(pid, argv);
            default: parent(pid, argv);
        }
        update(prompt);
    }
    shellCleanup(prompt, argv);
}

void boot() {
    sigHandlerSetup();
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}
