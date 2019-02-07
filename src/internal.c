/**
 * Ben Walker
 * CIS*3110
 * 
 * A library for running internal shell commands.
 */

#include "internal.h"
#include "gcdBuiltin.h"
#include "argsBuiltin.h"
#include "randBuiltin.h"
#include "argsHandler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * shellGcd()
 * Run the internal 'gcd' command and print result/usage statement
 */
void shellGcd(const char *cmd, const char *num1, const char *num2) {
    char *pretty = gcdPretty(num1, num2);
    if (pretty == NULL) {
        fprintf(stderr, "Usage: %s number1 number2\n", cmd);
        return;
    }
    fprintf(stdout, "%s\n", pretty);
    free(pretty);
}

/**
 * shellArgs()
 * Run the internal 'args' command and print result/usage statement
 */
void shellArgs(char **argv) {
    char *args = NULL;
    int argc;
    argsIndex(argv, &args, &argc); // populate args and argc
    !args
        ? fprintf(stderr, "Usage: %s ...options...\n", ARGS_CMD)
        : printf("argc = %d, args = %s\n", argc, args);
    free(args);
}

/**
 * shellRand()
 * Run the internal 'rand' command and print result
 */
void shellRand(const char *min, const char *max) {
    printf("%d\n", randomRange(min, max));
}

/**
 * isInternal()
 * Returns true if the string cmd is an internal shell command
 */
bool isInternal(const char *cmd) {
    const char *builtins[] = { GCD_CMD, ARGS_CMD, RAND_CMD };
    int len = sizeof(builtins) / sizeof(builtins[0]); // calculate list length

    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, builtins[i]) == 0)
            return true;
    return false;
}

/**
 * runInternal()
 * Setup I/O redirections, then determine/run the correct builtin
 */
void runInternal(char **argv) {
    const char *cmd = argv[0];

    if (strcmp(cmd, GCD_CMD) == 0)
        shellGcd(cmd, argv[1], argv[2]);
    else if (strcmp(cmd, ARGS_CMD) == 0)
        shellArgs(argv);
    else if (strcmp(cmd, RAND_CMD) == 0)
        shellRand(argv[1], argv[2]);
    exit(EXIT_SUCCESS);
}
