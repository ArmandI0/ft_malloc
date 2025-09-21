// #include "malloc.h"


// void free(void *ptr) {


// }
// void *malloc(size_t size) {

// }

#include <unistd.h>
#include <stdio.h>
#include "../include/malloc.h"

int main() {

	char *test = malloc(200);
	if (test == NULL) {
		printf("CONNARD");
		return 1;
	}

	for (int i = 0; i < 8; i++) {
		printf("%d\n", i);
		test[i] = 'c';
	}

	for (int i = 0; i < 100000; i++) {
		printf("%d\n", i);
		test = malloc(250000);
		if (test == NULL) {
			printf("MALLOC ERROR\n");
			return 0;
		}
	}
	return 0;
}