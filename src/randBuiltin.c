/**
 * Ben Walker
 * CIS*3110
 * 
 * Implementation of the 'rand' builtin command
 */

#include "randBuiltin.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

const char *RAND_CMD = "rand";
static bool init = false; // tracks whether random generation has been initialized

/**
 * seedRandom()
 * Seed random number generation, use static var to ensure it
 * only happens once.
 */
void seedRandom() {
    if (!init) {
        srand(time(NULL));
        init = true;
    }
}

/**
 * randomRange()
 * Returns a random integer in a user defined range
 */
int randomRange(const char *minRaw, const char *maxRaw) {
    seedRandom();
    int max = 100, min = 0;
    return rand() % (max + 1 - min) + min;
}
