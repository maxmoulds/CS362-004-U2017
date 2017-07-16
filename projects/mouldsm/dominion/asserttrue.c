#include <stdio.h>
#include "asserttrue.h"

void asserttrue(int a, int b) {
	if (a != b) {
		printf("TEST FAILED %d != %d\n", a, b);
	}
	else if (a == b) {
		printf("TEST SUCCESSFULLY PASSED %d == %d\n", a, b);
	} 
	else {
		printf("TEST FAILED ERR\n");
	}
}
