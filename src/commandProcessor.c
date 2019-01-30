#include "commandProcessor.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isBlank(char **args) {
    return args[0] == NULL;
}

bool isExit(char **args) {
    return strncmp("exit", args[0], strlen(args[0])) == 0;
}

int processCommand(char **args) {
    if (isBlank(args)) return 0;
    if (isExit(args)) return -1;
}
