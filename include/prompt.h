/**
 * Ben Walker
 * CIS*3110
 * 
 * A library for handling user prompt data.
 * Operates on struct Prompt.
 */

#ifndef PROMPT_
#define PROMPT_

#define _BSD_SOURCE // enables gethostname()

#include <stdbool.h>

/**
 * struct Prompt
 * Contains data relevant to the user prompt
 */
typedef struct Prompt {
    char *username;
    char *machine;
    char *comm; // the actual prompt string to display
    bool isRoot; // true if user is root
} Prompt;

Prompt *newPrompt();

void update(Prompt *prompt);

void destroy(Prompt *prompt);

#endif // PROMPT_
