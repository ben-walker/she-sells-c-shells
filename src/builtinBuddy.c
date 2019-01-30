#include "builtinBuddy.h"
#include <string.h>

bool internalCmd(const char *cmd) {
    const char *builtins[] = { GCD, ARGS };
    int len = sizeof(builtins) / sizeof(builtins[0]);

    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, builtins[i]) == 0)
            return true;
    return false;
}
