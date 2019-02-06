/**
 * Ben Walker
 * CIS*3110
 * 
 * Implementation of the 'gcd' builtin to find the greatest
 * common divisor of two numbers (int or hex)
 */

#ifndef GCD_BUILTIN_
#define GCD_BUILTIN_

extern const char *GCD_CMD; // name of the command for external use

int gcd(const char *valOne, const char *valTwo);

char *gcdPretty(const char *valOne, const char *valTwo);

#endif // GCD_BUILTIN_
