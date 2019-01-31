#include "external.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int runExternal(char **args) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Failed to fork new process");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("Failed to execute");
        return EXIT_FAILURE;
    } else {
        wait(NULL);
    }
    return EXIT_SUCCESS;
}
