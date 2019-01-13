#ifndef SHELL_DATA_GRABBER_
#define SHELL_DATA_GRABBER_

#include <stdbool.h>

typedef struct User
{
    char *username;
    char *machine;
    bool isRoot;
} User;

User *newUser();

void populate(User *shellUser);

char *getPrompt(User *shellUser, const char *defPrompt, const char *suPrompt);

#endif // SHELL_DATA_GRABBER_
