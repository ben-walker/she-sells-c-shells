#include "external.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool background(char **args) {
    char *lastArg;
    for (int i = 0; args[i] != NULL; lastArg = args[i], i += 1);
    return strcmp(lastArg, "&") == 0;
}

int forkFailed() {
    perror("Failed to fork new process");
    return EXIT_FAILURE;
}

void parentProcess() {
    wait(NULL);
}

int childProcess(char **args) {
    execvp(args[0], args);
    perror("Failed to execute");
    return EXIT_FAILURE;
}

int runExternal(char **args) {
    pid_t pid = fork();
    switch (pid) {
        case -1: return forkFailed();
        case 0: return childProcess(args);
        default: parentProcess();
    }
    return EXIT_SUCCESS;
}
