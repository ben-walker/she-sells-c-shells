#include "external.h"
#include "specialArgs.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void runExternal(char **argv) {
    char **newArgv = assignRedirections(argv);
    execvp(newArgv[0], newArgv);
    perror("execvp");
    exit(EXIT_FAILURE);
}
