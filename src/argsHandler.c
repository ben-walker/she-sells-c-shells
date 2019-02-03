#include "argsHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **getln();

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
