#include "../include/malloc.h"
#include <sys/resource.h>

int main() {
    size_t nb_page_fault = print_page_faults();  // ← Page faults AVANT tes malloc
    int i;
    char    *addr;
    i = 0;

    while (i < 1)
    {
        addr = (char *)malloc(580);
        addr[0] = 42;
        i++;
    }
    show_alloc_mem();
    return 0;
}