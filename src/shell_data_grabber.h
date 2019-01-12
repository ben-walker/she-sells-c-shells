#ifndef SHELL_DATA_GRABBER_
#define SHELL_DATA_GRABBER_

#include <stdbool.h>

typedef struct User
{
    char *username;
    char *machine;
    bool isRoot;
} User;

void populate(User *shellUser);

#endif // SHELL_DATA_GRABBER_
