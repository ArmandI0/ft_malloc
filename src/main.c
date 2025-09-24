#include "../include/malloc.h"

// int main() {

// 	// char *test = malloc(200);
// 	// if (test == NULL) {
// 	// 	printf("CONNARD");
// 	// 	return 1;
// 	// }

// 	// for (int i = 0; i < 8; i++) {
// 	// 	printf("%d\n", i);
// 	// 	test[i] = 'c';
// 	// }

// 	char * test;
// 	for (int i = 0; i < 100000; i++) {
// 		printf("%d\n", i);
// 		test = malloc(100);
// 		if (test == NULL) {
// 			return 0;
// 		}
// 	}

// 	return 0;
// }

int main() {
    int i;
    char    *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char *)malloc(1024);
        addr[0] = 42;
        i++;
    }
    return 0;
}