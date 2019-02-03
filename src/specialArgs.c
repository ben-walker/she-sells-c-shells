#include "specialArgs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

enum { NUM_ARGS = 100 };
const char *OUT_W = ">";
const char *IN_R = "<";

bool cmdIsRedir(const char *cmd) {
    const char *redirs[] = { OUT_W, IN_R };
    int len = sizeof(redirs) / sizeof(redirs[0]);
    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, redirs[i]) == 0)
            return true;
    return false;
}

void buildArgs(char **argv, int *argc, const char *new) {
    argv[*argc] = strdup(new);
    if (!argv[*argc]) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    *argc = *argc + 1;
}

void redirectStream(const char *fd, const char *mode, FILE *stream) {
    if (freopen(fd, mode, stream) == NULL) {
        perror("freopen");
        exit(EXIT_FAILURE);
    }
}

char **assignRedirections(char **argv) {
    int argc = 0;
    char *cmd, *fd;
    char **newArgs = malloc(NUM_ARGS * sizeof(char *));
    if (!newArgs) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    memset(newArgs, 0, NUM_ARGS);

    for (int i = 0; argv[i] != NULL; i += 1) {
        cmd = argv[i];
        fd = argv[i + 1];
        if (cmdIsRedir(cmd))
            i += 1;

        if (strcmp(cmd, OUT_W) == 0)
            redirectStream(fd, "w", stdout);
        else if (strcmp(cmd, IN_R) == 0)
            redirectStream(fd, "r", stdin);
        else
            buildArgs(newArgs, &argc, cmd);
    }
    return newArgs;
}
