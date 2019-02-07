/**
 * Ben Walker
 * CIS*3110
 * 
 * Library to convert a string to a number
 */

#include "numberHelp.h"
#include <stdlib.h>
#include <limits.h>

/**
 * convertToNum()
 * Convert string to integer, populate int pointer with result
 */
int convertToNum(const char *val, int *numeric) {
    if (!val) return EXIT_FAILURE;
    char *end = NULL;
    long converted = strtol(val, &end, 0);

    // detect possible strtol errors
    if (converted == LONG_MAX || converted == LONG_MIN || end == val)
        return EXIT_FAILURE;
    *numeric = converted;
    return EXIT_SUCCESS;
}
