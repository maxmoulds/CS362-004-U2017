#include <stdio.h>
#include <stdlib.h>

void assert_print(int condition) {
    if (condition) {
        printf("PASS");
    } else {
        printf("FAIL");
    }
}

// Returns a random integer in the range [low, high], inclusive.
int randInt(int low, int high) {
    return low + rand() % (high - low + 1);
}
