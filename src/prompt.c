/**
 * Ben Walker
 * CIS*3110
 * 
 * A library for handling user prompt data.
 * Operates on struct Prompt.
 */

#include "prompt.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

static const char *DEF_PROMPT = "$"; // prompt terminator for reg user
static const char *ROOT_PROMPT = "#"; // prompt terminator for su user
static const char *SEPARATOR = ":"; // separator for username and machine

/**
 * getUsername()
 * Get current username (left side of prompt)
 */
char *getUsername() {
    const struct passwd *pws = getpwuid(getuid()); // get user struct for current uid
    if (!pws) {
        fprintf(stderr, "Could not find username.");
        exit(EXIT_FAILURE);
    }
    return pws->pw_name;
}

/**
 * getMachine()
 * Get current machine name (right side of prompt)
 */
char *getMachine() {
    char *machine = malloc(_SC_HOST_NAME_MAX);
    if (!machine) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (gethostname(machine, _SC_HOST_NAME_MAX) != 0) {
        fprintf(stderr, "Could not find hostname.");
        exit(EXIT_FAILURE);
    }
    return machine;
}

/**
 * isRoot()
 * Return true if user is root
 */
bool isRoot() {
    return geteuid() == 0; // effective user id
}

/**
 * getPromptCommand()
 * Constructs prompt string from username, machine, root status
 */
char *getPromptCommand(const char *username, const char *machine, const bool root) {
    const char *promptTerminator = root ? ROOT_PROMPT : DEF_PROMPT;
    const size_t space = snprintf(NULL, 0, "%s%s%s%s", username, SEPARATOR, machine, promptTerminator) + 1;
    if (space < 0) {
        fprintf(stderr, "Could not determine prompt size.");
        exit(EXIT_FAILURE);
    }
    char *comm = malloc(space);
    if (!comm) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (sprintf(comm, "%s%s%s%s", username, SEPARATOR, machine, promptTerminator) < 0) {
        fprintf(stderr, "Could not construct prompt.");
        exit(EXIT_FAILURE);
    }
    return comm;
}

/**
 * clear()
 * Release all internal prompt memory, reset root status
 */
void clear(Prompt *prompt) {
    free(prompt->username);
    free(prompt->machine);
    free(prompt->comm);
    prompt->isRoot = false;
}

/**
 * populate()
 * Populates a preallocated prompt struct w/ username, machine, root status, prompt string
 */
void populate(Prompt *prompt) {
    prompt->username = strdup(getUsername());
    prompt->machine = strdup(getMachine());
    prompt->isRoot = isRoot();
    if (!prompt->username || !prompt->machine) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    prompt->comm = getPromptCommand(prompt->username, prompt->machine, prompt->isRoot);
    if (prompt->comm == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}

/**
 * newPrompt()
 * Allocate, populate, and return a new struct Prompt
 */
Prompt *newPrompt() {
    Prompt *prompt = malloc(sizeof(Prompt));
    if (!prompt) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    populate(prompt);
    return prompt;
}

/**
 * update()
 * Clear out all current prompt data, repopulate.
 */
void update(Prompt *prompt) {
    clear(prompt);
    populate(prompt);
}

/**
 * destroy()
 * Like clear(), but it also releases the actual prompt mem itself
 */
void destroy(Prompt *prompt) {
    free(prompt->username);
    free(prompt->machine);
    free(prompt->comm);
    free(prompt);
}
