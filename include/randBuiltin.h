/**
 * Ben Walker
 * CIS*3110
 * 
 * Implementation of the 'rand' builtin command
 */

#ifndef RAND_BUILTIN_
#define RAND_BUILTIN_

extern const char *RAND_CMD; // name of the command for external use

int randomRange(const char *min, const char *max);

#endif // RAND_BUILTIN_
