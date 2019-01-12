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

void populate(User *shellUser) {
    shellUser->username = strdup(getUsername());
    shellUser->machine = strdup(getMachine());
    if (!shellUser->username || !shellUser->machine) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    shellUser->isRoot = isUserRoot();
}
