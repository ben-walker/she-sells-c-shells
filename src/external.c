#include "external.h"
#include "specialArgs.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int forkFailed() {
    perror("Failed to fork new process");
    return EXIT_FAILURE;
}

int childProcess(char **args) {
    char **argv = assignRedirections(args);
    execvp(argv[0], argv);
    perror("execvp");
    exit(EXIT_FAILURE);
}

void parentProcess() {
    wait(NULL);
}

int runExternal(char **args) {
    pid_t pid = fork();
    switch (pid) {
        case -1: return forkFailed();
        case 0: childProcess(args);
        default: parentProcess();
    }
    return EXIT_SUCCESS;
}
