#include "argsBuiltin.h"
#include <stdlib.h>
#include <stdio.h>

const char *ARGS_CMD = "args";

int calcArgc(char **argv) {
    int argc;
    for (argc = 1; argv[argc] != NULL; argc += 1);
    return argc - 1;
}

void argsIndex(char **argv, char **args, int *argc) {
    char *format;
    size_t space;
    *argc = calcArgc(argv);

    for (int i = 1; argv[i] != NULL; i += 1) {
        format = argv[i + 1] == NULL ? "%s%s" : "%s%s, ";
        space = snprintf(NULL, 0, format, *args, argv[i]) + 1;
        if (space < 0) {
            fprintf(stderr, "Could not determine size.");
            exit(EXIT_FAILURE);
        }
        *args = realloc(*args, space);
        if (!*args) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        if (sprintf(*args, format, *args, argv[i]) < 0) {
            fprintf(stderr, "String write failed.");
            exit(EXIT_FAILURE);
        }
    }
}
