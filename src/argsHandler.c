#include "argsHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **getln();

enum { NUM_ARGS = 100 };
static const char *OUT_W = ">";
static const char *IN_R = "<";
static const char *BACK = "&";

void getArgs(const char *prompt, char ***line) {
    printf("%s ", prompt);
    *line = getln();
}

void freeArgs(char **argv) {
    for (int i = 0; argv[i] != NULL; i += 1)
        free(argv[i]);
}

bool isBlank(char **argv) {
    return argv[0] == NULL;
}

bool isInternalExit(char **argv) {
    return strcmp(argv[0], "exit") == 0;
}

bool isBackground(char **argv) {
    char *lastArg = NULL;
    for (int i = 0; argv[i] != NULL; i += 1)
        lastArg = argv[i];
    return strcmp(lastArg, BACK) == 0;
}

bool cmdIsRedirect(const char *cmd) {
    const char *redirs[] = { OUT_W, IN_R };
    int len = sizeof(redirs) / sizeof(redirs[0]);
    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, redirs[i]) == 0)
            return true;
    return false;
}

void redirectStream(const char *fd, const char *mode, FILE *stream) {
    if (freopen(fd, mode, stream) == NULL) {
        perror("freopen");
        exit(EXIT_FAILURE);
    }
}

void buildArgs(char **argv, int *argc, const char *new) {
    argv[*argc] = strdup(new);
    if (!argv[*argc]) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    *argc = *argc + 1;
}

char **assignRedirections(char **argv) {
    int argc = 0;
    char *cmd, *fd;
    char **args = malloc(NUM_ARGS * sizeof(char *));
    if (!args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memset(args, 0, NUM_ARGS);

    for (int i = 0; argv[i] != NULL; i += 1) {
        cmd = argv[i];
        fd = argv[i + 1];
        if (cmdIsRedirect(cmd))
            i += 1;

        if (strcmp(cmd, OUT_W) == 0)
            redirectStream(fd, "w", stdout);
        else if (strcmp(cmd, IN_R) == 0)
            redirectStream(fd, "r", stdin);
        else
            buildArgs(args, &argc, cmd);
    }
    return args;
}
