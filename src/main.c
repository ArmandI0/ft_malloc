// #include "malloc.h"


// void free(void *ptr) {


// }
// void *malloc(size_t size) {

// }

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int main() {

	int page_size = getpagesize();
	void *ptr = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!ptr) {
		return -1;
	}
	else {
		printf("toto\n");
	}
	munmap(ptr, page_size);
	return 0;
}