// #include "malloc.h"


// void free(void *ptr) {


// }
// void *malloc(size_t size) {

// }

// #include <unistd.h>
// #include <stdio.h>
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
// 	for (int i = 0; i < 19; i++) {
// 		printf("%d\n", i);
// 		test = malloc(250);
// 		if (test == NULL) {
// 			printf("MALLOC ERROR\n");
// 			return 0;
// 		}
// 		free(test);
// 	}

// 	return 0;
// }

// int main () {
//     char	bit_memory_map[SIZE_OF_BITMAP] = {0};

// 	ft_memset(bit_memory_map, 0, SIZE_OF_BITMAP);
//     mask_empty_bitmap(bit_memory_map, SMALL);
// 	set_bitmap(bit_memory_map, true, 254);
//     print_bitmap(bit_memory_map, SIZE_OF_BITMAP);
// 	// for (int i = 0; i < 32; i++) {
//     //     printf("%d", bit_memory_map[i]);
//     // }

// 	printf("is empty = %d\n", memory_is_empty(bit_memory_map, SMALL));
//     return 0;
// };