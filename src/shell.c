#include "shell.h"
#include "prompt.h"
#include <stdio.h>
#include <string.h>

extern char **getln();

void getCommand(const char *prompt, char ***line) {
    printf("%s ", prompt);
    *line = getln();
}

void commandLoop(Prompt *prompt) {
    char **args;

    while (true) {
        getCommand(prompt->comm, &args);
    }
}

void boot() {
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}
