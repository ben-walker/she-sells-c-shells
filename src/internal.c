#include "internal.h"
#include "gcdBuiltin.h"
#include "specialArgs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void shellGCD(const char *cmd, const char *num1, const char *num2) {
    char *pretty = gcdPretty(num1, num2);
    if (pretty == NULL) {
        fprintf(stderr, "Usage: %s number1 number2\n", cmd);
        return;
    }
    fprintf(stdout, "%s\n", pretty);
    free(pretty);
}

void shellArgs(const char *cmd, char **argv) {
    int argc;
    char *argsList = NULL, *format;
    size_t space;

    for (argc = 1; argv[argc] != NULL; argc += 1) {
        format = argv[argc + 1] == NULL ? "%s%s" : "%s%s, ";
        space = snprintf(NULL, 0, format, argsList, argv[argc]) + 1;
        if (space < 0) {
            fprintf(stderr, "Could not determine size.");
            exit(EXIT_FAILURE);
        }
        argsList = realloc(argsList, space);
        if (!argsList) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        if (sprintf(argsList, format, argsList, argv[argc]) < 0) {
            fprintf(stderr, "String write failed.");
            exit(EXIT_FAILURE);
        }
    }

    if (!argsList) {
        fprintf(stderr, "Usage: %s ...options...\n", cmd);
        return;
    }
    printf("argc = %d, args = %s\n", argc - 1, argsList);
    free(argsList);
}

bool isInternal(const char *cmd) {
    const char *builtins[] = { GCD_CMD, ARGS };
    int len = sizeof(builtins) / sizeof(builtins[0]);

    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, builtins[i]) == 0)
            return true;
    return false;
}

void runInternal(char **argv) {
    char **newArgv = assignRedirections(argv);
    const char *cmd = newArgv[0];

    if (strcmp(cmd, GCD_CMD) == 0)
        shellGCD(newArgv[0], newArgv[1], newArgv[2]);
    else if (strcmp(cmd, ARGS) == 0)
        shellArgs(ARGS, argv);
    exit(EXIT_SUCCESS);
}
