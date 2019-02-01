#include "external.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static const char *BACKGROUND = "&";

bool background(char **args) {
    char *lastArg;
    for (int i = 0; args[i] != NULL; i += 1)
        lastArg = args[i];
    return strcmp(lastArg, BACKGROUND) == 0;
}

void removeAt(const int pos, const int mod, char **args) {
    for (int i = 0; i < mod; i += 1)
        for (int j = pos; args[j] != NULL; j += 1)
            args[j] = args[j + 1];
}

void assignRedirections(char **args) {
    int i = 0;

    while (args[i] != NULL) {
        const char *cmd = args[i], *fd = args[i + 1];
        if (strcmp(cmd, ">") == 0) {
            freopen(fd, "w", stdout);
            removeAt(i, 2, args);
            continue;
        } else if (strcmp(cmd, "<") == 0) {
            freopen(fd, "r", stdin);
            removeAt(i, 2, args);
            continue;
        }
        i += 1;
    }
}

int forkFailed() {
    perror("Failed to fork new process");
    return EXIT_FAILURE;
}

void parentProcess() {
    wait(NULL);
}

int childProcess(char **args) {
    assignRedirections(args);
    execvp(args[0], args);
    perror("execvp");
    exit(EXIT_FAILURE);
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
