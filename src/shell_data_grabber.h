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

char *getPrompt(User *shellUser, char *defPrompt, char *suPrompt);

#endif // SHELL_DATA_GRABBER_
