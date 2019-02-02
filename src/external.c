#include "external.h"
#include "specialArgs.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void runExternal(char **argv) {
    char **newArgv = assignRedirections(argv);
    execvp(newArgv[0], newArgv);
    perror("execvp");
    exit(EXIT_FAILURE);
}
