#include "specialArgs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum { NUM_ARGS = 100 };

char **assignRedirections(char **argv) {
    int i = 0, argCount = 0;
    char *cmd, *fd;
    char **newArgs = malloc(NUM_ARGS * sizeof(char *));
    if (!newArgs) {
        perror("Memory allocation failed newargs");
        exit(EXIT_FAILURE);
    }
    memset(newArgs, 0, NUM_ARGS);

    for (int i = 0; argv[i] != NULL; i += 1) {
        cmd = argv[i];
        fd = argv[i + 1];

        if (strcmp(cmd, ">") == 0) {
            freopen(fd, "w", stdout);
            i += 1;
        } else if (strcmp(cmd, "<") == 0) {
            freopen(fd, "r", stdin);
            i += 1;
        } else {
            newArgs[argCount] = strdup(cmd);
            if (!newArgs[argCount]) {
                perror("Memory allocation failed newargs[i]");
                exit(EXIT_FAILURE);
            }
            argCount += 1;
        }
    }
    return newArgs;
}
