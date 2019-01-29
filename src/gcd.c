#include "gcd.h"
#include <stdlib.h>
#include <limits.h>

int convertToNum(const char *val, int *numeric) {
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
