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

int runExternal(char **args) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Failed to fork new process");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("Failed to execute");
        return EXIT_FAILURE;
    } else {
        wait(NULL);
    }
    return EXIT_SUCCESS;
}
