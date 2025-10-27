#include "../include/malloc.h"
#include <sys/resource.h>

int main() {
    char    *addr;

    // Premier bloc
    for (int i = 0; i < 10; i++) {
        addr = (char *)malloc(73);
        if (addr != NULL) addr[0] = 42;
		free(addr);

    }

	int a = 0;
	free(1);
    show_alloc_mem();
	show_alloc_mem();
	return 0;
}