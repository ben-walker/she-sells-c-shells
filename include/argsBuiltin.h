/**
 * Ben Walker
 * CIS*3110
 * 
 * Implementation of the 'args' builtin command
 */

#ifndef ARGS_BUILTIN_
#define ARGS_BUILTIN_

extern const char *ARGS_CMD; // name of the command for external use

void argsIndex(char **argv, char **args, int *argc);

#endif // ARGS_BUILTIN_
