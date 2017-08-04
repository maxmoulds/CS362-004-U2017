#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

void testCompare(void);
int compare(const void* a, const void* b);

int main(int argv, char **argc) {
    testCompare();
    return 0;
}

void testCompare(void) {
    int expectedReturn;

    // Compare every integer pairing in [SHRT_MIN, SHRT_MAX]
    for (int i = SHRT_MIN; i <= SHRT_MAX; ++i) {
        for (int j = SHRT_MIN; j <= SHRT_MAX; ++j) {
            if (i < j) {
                expectedReturn = -1;
            } else if (i > j) {
                expectedReturn = 1;
            } else {
                expectedReturn = 0;
            }

            assert(expectedReturn == compare(&i, &j));
        }
    }

    printf("ALL COMPARE TEST CASES PASSED\n");
}
