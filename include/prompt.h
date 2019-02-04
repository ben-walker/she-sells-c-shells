#ifndef PROMPT_
#define PROMPT_

#define _BSD_SOURCE

#include <stdbool.h>

typedef struct Prompt {
    char *username;
    char *machine;
    char *comm;
    bool isRoot;
} Prompt;

Prompt *newPrompt();

void update(Prompt *prompt);

void destroy(Prompt *prompt);

#endif // PROMPT_
