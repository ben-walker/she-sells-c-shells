#include "shell.h"
#include "prompt.h"
#include <stdio.h>
#include <string.h>

void commandLoop();

void boot() {
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}

void commandLoop(Prompt *prompt) {
    char *buff = NULL;
    size_t allocSize = 0;

    while (printf("%s ", prompt->comm) >= 0 && getline(&buff, &allocSize, stdin) != -1) {
        buff[strcspn(buff, "\r\n")] = 0;
    }
}
