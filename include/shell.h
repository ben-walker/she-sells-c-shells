/**
 * Ben Walker
 * CIS*3110
 * 
 * The main command loop for the shell.
 * Set up a signal handler for SIGCHLD signals,
 * get the next user command in a loop,
 * fork() to run/wait for the command,
 * cleanup memory when the user exits.
 */

#ifndef SHELL_
#define SHELL_

void boot();

#endif // SHELL_
