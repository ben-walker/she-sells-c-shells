#ifndef INTERNAL_
#define INTERNAL_

#include <stdbool.h>

static const char *GCD = "gcd";
static const char *ARGS = "args";

bool internalCmd(const char *cmd);

void runInternal(char **argv);

#endif // INTERNAL_
