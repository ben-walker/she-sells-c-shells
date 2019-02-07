/**
 * Ben Walker
 * CIS*3110
 * 
 * Implementation of the 'gcd' builtin to find the greatest
 * common divisor of two numbers (int or hex)
 */

#include "gcdBuiltin.h"
#include "numberHelp.h"
#include <stdlib.h>
#include <stdio.h>

const char *GCD_CMD = "gcd";

/**
 * recursiveGcd()
 * Calculate gcd recursively, return result
 */
int recursiveGcd(const int numOne, const int numTwo) {
    if (numTwo != 0)
        return(recursiveGcd(numTwo, numOne % numTwo));
    return numOne;
}

/**
 * gcd()
 * Use the above functions to calculate the gcd of two numbers
 * passed as strings.
 */
int gcd(const char *valOne, const char *valTwo) {
    int numOne, numTwo;
    if (convertToNum(valOne, &numOne) == EXIT_FAILURE ||
        convertToNum(valTwo, &numTwo) == EXIT_FAILURE)
        return -1;
    return recursiveGcd(numOne, numTwo);
}

/**
 * gcdPretty()
 * Format wrapper for gcd()
 */
char *gcdPretty(const char *valOne, const char *valTwo) {
    int gcdVal = gcd(valOne, valTwo);
    const char *template = "%s(%s, %s) = %d";
    if (gcdVal == -1)
        return NULL;

    const size_t space = snprintf(NULL, 0, template, GCD_CMD, valOne, valTwo, gcdVal) + 1;
    if (space < 0) {
        fprintf(stderr, "Could not form string.");
        exit(EXIT_FAILURE);
    }
    char *pretty = malloc(space);
    if (!pretty) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (sprintf(pretty, template, GCD_CMD, valOne, valTwo, gcdVal) < 0) {
        fprintf(stderr, "Could not construct gcd string.");
        exit(EXIT_FAILURE);
    }
    return pretty;
}
