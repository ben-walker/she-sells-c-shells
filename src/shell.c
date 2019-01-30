#include "shell.h"
#include "prompt.h"
#include "commandProcessor.h"
#include <stdio.h>
#include <stdlib.h>

extern char **getln();

void getArgs(const char *prompt, char ***line) {
    printf("%s ", prompt);
    *line = getln();
}

void freeArgs(char **args) {
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
}

void cleanup(Prompt *prompt, char **args) {
    destroy(prompt);
    freeArgs(args);
    exit(EXIT_SUCCESS);
}

void commandLoop(Prompt *prompt) {
    char **args;

    while (true) {
        getArgs(prompt->comm, &args);
        if (processCommand(args) == -1)
            break;
        update(prompt);
    }
    cleanup(prompt, args);
}

void boot() {
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}
