#include "shell.h"
#include "prompt.h"
#include "processSupervisor.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern char **getln();

void getArgs(const char *prompt, char ***line) {
    printf("%s ", prompt);
    *line = getln();
}

void destroyArgs(char **argv) {
    for (int i = 0; argv[i] != NULL; i += 1)
        free(argv[i]);
}

void cleanup(Prompt *prompt, char **argv) {
    destroy(prompt);
    destroyArgs(argv);
}

bool shouldExit(char **argv) {
    return strcmp(argv[0], "exit") == 0;
}

bool blank(char **argv) {
    return argv[0] == NULL;
}

void commandLoop(Prompt *prompt) {
    char **argv;

    while (true) {
        getArgs(prompt->comm, &argv);
        if (blank(argv)) continue;
        if (shouldExit(argv)) break;

        pid_t pid = fork();
        switch (pid) {
            case -1: perror("Failed to fork new process");
            case 0: child(pid, argv);
            default: wait(NULL);
        }
        update(prompt);
    }
    cleanup(prompt, argv);
}

void boot() {
    Prompt *prompt = newPrompt();
    commandLoop(prompt);
}
