// #include "malloc.h"


// void free(void *ptr) {


// }
// void *malloc(size_t size) {

// }

#include <unistd.h>
#include <stdio.h>
#include "../include/malloc.h"

int main() {

	// char *test = malloc(200);
	// if (test == NULL) {
	// 	printf("CONNARD");
	// 	return 1;
	// }

	// for (int i = 0; i < 8; i++) {
	// 	printf("%d\n", i);
	// 	test[i] = 'c';
	// }

	char * test;
	for (int i = 0; i < 19; i++) {
		printf("%d\n", i);
		test = malloc(250);
		if (test == NULL) {
			printf("MALLOC ERROR\n");
			return 0;
		}
		free(test);
	}

	return 0;
}