#include "shell.h"
#include "shell_data_grabber.h"
#include <stdio.h>
#include <string.h>

const char *DEF_PROMPT = "$";
const char *SU_PROMPT = "#";

void commandLoop();

void boot() {
    User *shellUser = newUser();
    populate(shellUser);
    const char *prompt = getPrompt(shellUser, DEF_PROMPT, SU_PROMPT);
    commandLoop(prompt);
}

void commandLoop(const char *prompt) {
    char *buff = NULL;
    size_t allocSize = 0;

    while (printf("%s ", prompt) >= 0 && getline(&buff, &allocSize, stdin) != -1) {
        buff[strcspn(buff, "\r\n")] = 0;
    }
}
