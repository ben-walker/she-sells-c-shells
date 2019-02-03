#include "gcdBuiltin.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int convertToNum(const char *val, int *numeric) {
    if (!val) return EXIT_FAILURE;
    char *end = NULL;
    long converted = strtol(val, &end, 0);

    if (converted == LONG_MAX || converted == LONG_MIN || end == val)
        return EXIT_FAILURE;
    *numeric = converted;
    return EXIT_SUCCESS;
}

int recursiveGcd(const int numOne, const int numTwo) {
    if (numTwo != 0)
        return(recursiveGcd(numTwo, numOne % numTwo));
    return numOne;
}

int gcd(const char *valOne, const char *valTwo) {
    int numOne, numTwo;
    if (convertToNum(valOne, &numOne) == EXIT_FAILURE ||
        convertToNum(valTwo, &numTwo) == EXIT_FAILURE)
        return -1;
    return recursiveGcd(numOne, numTwo);
}

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
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    if (sprintf(pretty, template, GCD_CMD, valOne, valTwo, gcdVal) < 0) {
        fprintf(stderr, "Could not construct gcd string.");
        exit(EXIT_FAILURE);
    }
    return pretty;
}
