#include "external.h"
#include "argsHandler.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void runExternal(char **argv) {
    char **newArgv = consumeSpecialArgs(argv);
    execvp(newArgv[0], newArgv);
    perror("execvp");
    exit(EXIT_FAILURE);
}
