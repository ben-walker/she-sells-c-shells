#ifndef SHELL_DATA_GRABBER_
#define SHELL_DATA_GRABBER_

#include <stdbool.h>

typedef struct User
{
    char *username;
    char *machine;
    bool isSuper;
    char prompt;
} User;

void initialize(User *shellUser);
char *getShellPrompt(User *shellUser);

#endif // SHELL_DATA_GRABBER_
