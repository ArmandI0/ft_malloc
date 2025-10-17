#include "../include/malloc.h"
#include <sys/resource.h>

size_t print_page_faults() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Minor page faults: %ld\n", usage.ru_minflt);
    return usage.ru_minflt;
}

int main() {
    size_t nb_page_fault = print_page_faults();  // ← Page faults AVANT tes malloc
    int i;
    char    *addr;
    i = 0;

    while (i < 1024)
    {
        addr = (char *)malloc(1024);
        addr[0] = 42;
        i++;
    }
    show_alloc_mem();
    nb_page_fault -= print_page_faults();  // ← Page faults APRÈS tes malloc
    printf("%ld", nb_page_fault);
    return 0;
}