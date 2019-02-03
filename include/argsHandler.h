#ifndef ARGS_HANDLER_
#define ARGS_HANDLER_

#include <stdbool.h>

void getArgs(const char *prompt, char ***line);

void freeArgs(char **argv);

bool isBlank(char **argv);

bool isInternalExit(char **argv);

bool isBackground(char **argv);

char **consumeSpecialArgs(char **argv);

#endif // ARGS_HANDLER_
