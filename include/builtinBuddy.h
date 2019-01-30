#ifndef BUILTIN_BUDDY_
#define BUILTIN_BUDDY_

#include <stdbool.h>

static const char *GCD = "gcd";
static const char *ARGS = "args";

bool internalCmd(const char *cmd);

void runInternal(char **args);

#endif // BUILTIN_BUDDY_
