/**
 * Ben Walker
 * CIS*3110
 * 
 * A library for processing a list of user arguments
 */

#include "argsHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **getln(); // function from parser.lex

enum { NUM_ARGS = 100 }; // max arguments in list
static const char *O_W = ">"; // write to stdout
static const char *O_A = ">>"; // append to stdout
static const char *E_W = "2>"; // write to stderr
static const char *E_A = "2>>"; // append to stderr
static const char *C_O_W = "&>"; // write to stderr/stdout
static const char *C_O_A = "&>>"; // append to stderr/stdout
static const char *I_R = "<"; // redirect stdin
static const char *BACK = "&"; // background process

/**
 * getArgs()
 * Show user prompt, return list of arguments
 */
void getArgs(const char *prompt, char ***line) {
    printf("%s ", prompt);
    *line = getln();
}

/**
 * freeArgs()
 * Release memory from argument list
 */
void freeArgs(char **argv) {
    for (int i = 0; argv[i] != NULL; i += 1)
        free(argv[i]);
}

/**
 * isBlank()
 * Return true if first argument is blank
 */
bool isBlank(char **argv) {
    return argv[0] == NULL;
}

/**
 * isInternalExit()
 * Return true if the command is 'exit'
 */
bool isInternalExit(char **argv) {
    return strcmp(argv[0], "exit") == 0;
}

/**
 * isBackground()
 * Return true if the last argument is '&'
 */
bool isBackground(char **argv) {
    char *lastArg = NULL;
    for (int i = 0; argv[i] != NULL; i += 1)
        lastArg = argv[i];
    return strcmp(lastArg, BACK) == 0;
}

/**
 * cmdIsRedirect()
 * Return true if the string is a file redirection operator
 */
bool cmdIsRedirect(const char *cmd) {
    const char *redirs[] = { O_W, O_A, E_W, E_A, C_O_W, C_O_A, I_R };
    int len = sizeof(redirs) / sizeof(redirs[0]);
    for (int i = 0; i < len; i += 1)
        if (strcmp(cmd, redirs[i]) == 0)
            return true;
    return false;
}

/**
 * redirectStream()
 * Assigns a stream (stdin, stdout) with a file name in a certain mode;
 * wrapper for freopen() with error handling.
 */
void redirectStream(const char *fd, const char *mode, FILE *stream) {
    if (freopen(fd, mode, stream) == NULL) {
        perror("freopen");
        exit(EXIT_FAILURE);
    }
}

/**
 * buildArgs()
 * Add an argument to a string array, increment arg counter
 */
void buildArgs(char **argv, int *argc, const char *new) {
    argv[*argc] = strdup(new);
    if (!argv[*argc]) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    *argc = *argc + 1;
}

/**
 * processRedirection()
 * Close/open streams and assign them to the passed in file descriptor
 */
void processRedirection(const char *redir, const char *fd) {
    if (strcmp(redir, O_W) == 0 || strcmp(redir, C_O_W) == 0)
        redirectStream(fd, "w", stdout);
    if (strcmp(redir, O_A) == 0 || strcmp(redir, C_O_A) == 0)
        redirectStream(fd, "a", stdout);
    if (strcmp(redir, E_W) == 0 || strcmp(redir, C_O_W) == 0)
        redirectStream(fd, "w", stderr);
    if (strcmp(redir, E_A) == 0 || strcmp(redir, C_O_A) == 0)
        redirectStream(fd, "a", stderr);
    if (strcmp(redir, I_R) == 0)
        redirectStream(fd, "r", stdin);
}

/**
 * consumeSpecialArgs()
 * Returns a new argument list without special arguments
 * (file redirections, background). Also assigns file redirections.
 */
char **consumeSpecialArgs(char **argv) {
    int argc = 0;
    char *cmd, *fd;
    char **args = malloc(NUM_ARGS * sizeof(char *));
    if (!args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memset(args, 0, NUM_ARGS);

    for (int i = 0; argv[i] != NULL; i += 1) {
        cmd = argv[i]; // the current arg
        fd = argv[i + 1]; // the next arg (file if cmd is redirection)

        if (cmdIsRedirect(cmd)) {
            i += 1; // don't add this command or the next to our new args list
            processRedirection(cmd, fd); // redirect out/input appropriately
        } else if (fd == NULL && isBackground(argv)) {
            continue; // if we're at the last arg and it's the background operator continue
        } else {
            buildArgs(args, &argc, cmd);
        }
    }
    return args;
}
