#include "internal.h"
#include "gcdBuiltin.h"
#include "argsBuiltin.h"
#include "argsHandler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void shellGcd(const char *cmd, const char *num1, const char *num2) {
    char *pretty = gcdPretty(num1, num2);
    if (pretty == NULL) {
        fprintf(stderr, "Usage: %s number1 number2\n", cmd);
        return;
    }
    fprintf(stdout, "%s\n", pretty);
    free(pretty);
}

void shellArgs(char **argv) {
    char *args = NULL;
    int argc;
    argsIndex(argv, &args, &argc);
    !args
        ? fprintf(stderr, "Usage: %s ...options...\n", ARGS_CMD)
        : printf("argc = %d, args = %s\n", argc, args);
    free(args);
}

bool isInternal(const char *cmd) {
    const char *builtins[] = { GCD_CMD, ARGS_CMD };
    int len = sizeof(builtins) / sizeof(builtins[0]);

    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, builtins[i]) == 0)
            return true;
    return false;
}

void runInternal(char **argv) {
    char **redirArgs = consumeSpecialArgs(argv);
    const char *cmd = redirArgs[0];

    if (strcmp(cmd, GCD_CMD) == 0)
        shellGcd(redirArgs[0], redirArgs[1], redirArgs[2]);
    else if (strcmp(cmd, ARGS_CMD) == 0)
        shellArgs(argv);

    freeArgs(redirArgs);
    exit(EXIT_SUCCESS);
}
