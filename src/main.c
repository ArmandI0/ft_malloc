#include "../include/malloc.h"
#include <sys/resource.h>

int main() {
    char    *addr;

    // Premier bloc
    for (int i = 0; i < 10; i++) {
        addr = (char *)malloc(580);
        if (addr != NULL) addr[0] = 42;
    }

    // Deuxième bloc
    for (int i = 0; i < 10; i++) {
        addr = (char *)malloc(48102162);
        if (addr != NULL) addr[0] = 42;
    }

    // Troisième bloc
    for (int i = 0; i < 10; i++) {
        addr = (char *)malloc(50);
        if (addr != NULL) addr[0] = 42;
    }
    show_alloc_mem();
    return 0;
}