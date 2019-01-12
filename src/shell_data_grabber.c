#include "shell_data_grabber.h"
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

const int MACHINE_BOUND = 50;

char *getUsername() {
    const struct passwd *pws = getpwuid(getuid());
    return pws->pw_name;
}

char *getMachine() {
    char *machine = malloc(MACHINE_BOUND);
    gethostname(machine, MACHINE_BOUND);
    return machine;
}

bool isUserRoot() {
    return geteuid() == 0;
}

void populate(User *shellUser) {
    shellUser->username = strdup(getUsername());
    shellUser->machine = strdup(getMachine());
    shellUser->isRoot = isUserRoot();
}
