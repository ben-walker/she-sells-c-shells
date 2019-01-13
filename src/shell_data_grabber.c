#include "shell_data_grabber.h"
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>

const int MACHINE_BOUND = 50;

char *getUsername() {
    const struct passwd *pws = getpwuid(getuid());
    if (!pws) {
        fprintf(stderr, "Could not find username.");
        exit(EXIT_FAILURE);
    }
    return pws->pw_name;
}

char *getMachine() {
    char *machine = malloc(MACHINE_BOUND);
    if (!machine) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    if (gethostname(machine, MACHINE_BOUND) != 0) {
        fprintf(stderr, "Could not find hostname.");
        exit(EXIT_FAILURE);
    }
    return machine;
}

bool isUserRoot() {
    return geteuid() == 0;
}

User *newUser() {
    User *user = malloc(sizeof(User));
    if (!user) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    return user;
}

void populate(User *shellUser) {
    shellUser->username = strdup(getUsername());
    shellUser->machine = strdup(getMachine());
    if (!shellUser->username || !shellUser->machine) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    shellUser->isRoot = isUserRoot();
}

char *getPrompt(User *shellUser, const char *defPrompt, const char *suPrompt) {
    const char *promptTerminator = shellUser->isRoot ? suPrompt : defPrompt;
    char *separator = ":";
    size_t space = snprintf(NULL, 0, "%s%s%s%s", shellUser->username, separator, shellUser->machine, promptTerminator) + 1;
    if (space < 0) {
        fprintf(stderr, "Could not determine prompt size.");
        exit(EXIT_FAILURE);
    }
    char *prompt = malloc(space);
    if (!prompt) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    if (sprintf(prompt, "%s%s%s%s", shellUser->username, separator, shellUser->machine, promptTerminator)  < 0) {
        fprintf(stderr, "Could not construct prompt.");
        exit(EXIT_FAILURE);
    }
    return prompt;
}
