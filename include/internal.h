/**
 * Ben Walker
 * CIS*3110
 * 
 * A library for running internal shell commands.
 */

#ifndef INTERNAL_
#define INTERNAL_

#include <stdbool.h>

bool isInternal(const char *cmd);

void runInternal(char **argv);

#endif // INTERNAL_
