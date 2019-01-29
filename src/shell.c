#include "shell.h"
#include "prompt.h"
#include <stdio.h>
#include <string.h>

void format(char *line) {
    line[strcspn(line, "\r\n")] = 0;
}

int getCommand(const char *prompt, char **line) {
    size_t allocSize;
    printf("%s ", prompt);
    return getline(line, &allocSize, stdin);
}

void commandLoop(Prompt *prompt) {
    char *buff = NULL;

    while (getCommand(prompt->comm, &buff) != -1) {
        format(buff);
    }
}

void boot() {
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}
