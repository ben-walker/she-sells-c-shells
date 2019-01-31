#include "builtinBuddy.h"
#include "gcd.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int shellGCD(const char *cmd, const char *num1, const char *num2) {
    int bigDiv = gcd(num1, num2);
    if (bigDiv == -1) {
        fprintf(stderr, "Usage: %s number1 number2\n", cmd);
        return EXIT_FAILURE;
    }
    printf("GCD(%s, %s) = %d\n", num1, num2, bigDiv);
    return EXIT_SUCCESS;
}

int shellArgs(const char *cmd, char **args) {
    int argc;
    char *argsList = NULL, *format;
    size_t space;

    for (argc = 1; args[argc] != NULL; argc += 1) {
        format = args[argc + 1] == NULL ? "%s%s" : "%s%s, ";
        space = snprintf(NULL, 0, format, argsList, args[argc]) + 1;
        if (space < 0) {
            fprintf(stderr, "Could not determine size.");
            exit(EXIT_FAILURE);
        }
        argsList = realloc(argsList, space);
        if (!argsList) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        if (sprintf(argsList, format, argsList, args[argc]) < 0) {
            fprintf(stderr, "String write failed.");
            exit(EXIT_FAILURE);
        }
    }

    if (!argsList) {
        fprintf(stderr, "Usage: %s ...options...\n", cmd);
        return EXIT_FAILURE;
    }
    printf("argc = %d, args = %s\n", argc - 1, argsList);
    free(argsList);
    return EXIT_SUCCESS;
}

bool internalCmd(const char *cmd) {
    const char *builtins[] = { GCD, ARGS };
    int len = sizeof(builtins) / sizeof(builtins[0]);

    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, builtins[i]) == 0)
            return true;
    return false;
}

int runInternal(char **args) {
    const char *cmd = args[0];

    if (strcmp(cmd, GCD) == 0)
        return shellGCD(args[0], args[1], args[2]);
    else if (strcmp(cmd, ARGS) == 0)
        return shellArgs(ARGS, args);
    return -1;
}
