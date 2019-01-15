#include "prompt.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

const char *DEF_PROMPT = "$";
const char *ROOT_PROMPT = "#";
const char *SEPARATOR = ":";

char *getUsername() {
    const struct passwd *pws = getpwuid(getuid());
    if (!pws) {
        fprintf(stderr, "Could not find username.");
        exit(EXIT_FAILURE);
    }
    return pws->pw_name;
}

char *getMachine() {
    char *machine = malloc(_SC_HOST_NAME_MAX);
    if (!machine) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    if (gethostname(machine, _SC_HOST_NAME_MAX) != 0) {
        fprintf(stderr, "Could not find hostname.");
        exit(EXIT_FAILURE);
    }
    return machine;
}

bool isRoot() {
    return geteuid() == 0;
}

char *getPromptCommand(const char *username, const char *machine, const bool root) {
    const char *promptTerminator = root ? ROOT_PROMPT : DEF_PROMPT;
    const size_t space = snprintf(NULL, 0, "%s%s%s%s", username, SEPARATOR, machine, promptTerminator) + 1;
    if (space < 0) {
        fprintf(stderr, "Could not determine prompt size.");
        exit(EXIT_FAILURE);
    }
    char *comm = malloc(space);
    if (!comm) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    if (sprintf(comm, "%s%s%s%s", username, SEPARATOR, machine, promptTerminator) < 0) {
        fprintf(stderr, "Could not construct prompt.");
        exit(EXIT_FAILURE);
    }
    return comm;
}

void clear(Prompt *prompt) {
    free(prompt->username);
    free(prompt->machine);
    free(prompt->comm);
    prompt->isRoot = false;
}

void populate(Prompt *prompt) {
    prompt->username = strdup(getUsername());
    prompt->machine = strdup(getMachine());
    prompt->isRoot = isRoot();
    if (!prompt->username || !prompt->machine) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    prompt->comm = strdup(getPromptCommand(prompt->username, prompt->machine, prompt->isRoot));
    if (!prompt->comm) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
}

Prompt *newPrompt() {
    Prompt *prompt = malloc(sizeof(Prompt));
    if (!prompt) {
        fprintf(stderr, "Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    populate(prompt);
    return prompt;
}

void update(Prompt *prompt) {
    clear(prompt);
    populate(prompt);
}

void destroy(Prompt *prompt) {
    free(prompt->username);
    free(prompt->machine);
    free(prompt->comm);
    free(prompt);
}
