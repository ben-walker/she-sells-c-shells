#include "shell.h"
#include "prompt.h"
#include "builtinBuddy.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern char **getln();

void getArgs(const char *prompt, char ***line) {
    printf("%s ", prompt);
    *line = getln();
}

void destroyArgs(char **args) {
    for (int i = 0; args[i] != NULL; i += 1)
        free(args[i]);
}

void cleanup(Prompt *prompt, char **args) {
    destroy(prompt);
    destroyArgs(args);
    exit(EXIT_SUCCESS);
}

bool shouldExit(char **args) {
    return strcmp(args[0], "exit") == 0;
}

void commandLoop(Prompt *prompt) {
    char **args;

    while (true) {
        getArgs(prompt->comm, &args);
        if (shouldExit(args))
            break;
        update(prompt);
    }
    cleanup(prompt, args);
}

void boot() {
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}
