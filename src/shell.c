#include "shell.h"
#include "prompt.h"
#include "builtinBuddy.h"
#include "external.h"
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

bool blank(char **args) {
    return args[0] == NULL;
}

void commandLoop(Prompt *prompt) {
    char **args;

    while (true) {
        getArgs(prompt->comm, &args);
        if (blank(args)) continue;
        if (shouldExit(args)) break;
        internalCmd(args[0]) ? runInternal(args) : runExternal(args);
        update(prompt);
    }
    cleanup(prompt, args);
}

void boot() {
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}
