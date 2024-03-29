/**
 * Ben Walker
 * CIS*3110
 * 
 * A simple library to run an external command
 */

#include "external.h"
#include "argsHandler.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * runExternal()
 * Execute an external shell command
 */
void runExternal(char **argv) {
    execvp(argv[0], argv);
    perror("execvp"); // execvp only returns if there's an error
    exit(EXIT_FAILURE);
}
