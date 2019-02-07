/**
 * Ben Walker
 * CIS*3110
 * 
 * Implementation of the 'rand' builtin command
 */

#include "randBuiltin.h"
#include "numberHelp.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

const char *RAND_CMD = "rand";
static bool init = false; // tracks whether random generation has been initialized
const int DEF_MIN = 0; // default minimum random value
const int DEF_MAX = 100; // default maximum random value

/**
 * seedRandom()
 * Seed random number generation, use static var to ensure it
 * only happens once.
 */
void seedRandom() {
    if (!init) {
        struct timeval time;
        gettimeofday(&time, NULL);
        srand((time.tv_sec * 1000) + (time.tv_usec / 1000)); // initialize random with microsecond resolution
        init = true;
    }
}

/**
 * randomRange()
 * Returns a random integer in a user defined range
 */
int randomRange(const char *minRaw, const char *maxRaw) {
    seedRandom();
    int min = -1, max = -1;
    convertToNum(minRaw, &min);
    convertToNum(maxRaw, &max);
    min = min == -1 ? DEF_MIN : min;
    max = max == -1 ? DEF_MAX : max;
    return rand() % (max + 1 - min) + min;
}
