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

bool internalCmd(const char *cmd) {
    const char *builtins[] = { GCD, ARGS };
    int len = sizeof(builtins) / sizeof(builtins[0]);

    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, builtins[i]) == 0)
            return true;
    return false;
}

void runInternal(char **args) {
    const char *cmd = args[0];

    if (strcmp(cmd, GCD) == 0)
        shellGCD(args[0], args[1], args[2]);
    else if (strcmp(cmd, ARGS) == 0)
        NULL;
}
