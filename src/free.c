#include "../include/malloc.h"

#include <stdio.h>

void print_sheader(struct s_header *header, int is_large) {
    if (!header) {
        printf("Header is NULL\n");
        return;
    }

    printf("Header at %p\n", (void*)header);
    printf("Size: %zu bytes\n", header->size);

    if (is_large) {
        printf("Large page:\n");
        printf("  Previous page: %p\n", (void*)header->body.large_size.previous_page);
        printf("  Next page    : %p\n", (void*)header->body.large_size.next_page);
    } else {
        printf("Normal page:\n");
        printf("  Free fragments remaining: %d\n", header->body.normal_size.free_fragments_remaining);
        printf("  Fragments start         : %p\n", (void*)header->body.normal_size.fragments_start);
        printf("  Next page               : %p\n", (void*)header->body.normal_size.next_page);
    }
}

// Faire un filtre pour voir si la zone est vide
void free_operation(struct s_header *header, void *ptr) {
    char    *bitmap = (char *)(header + HEADER_SIZE);
    char	bit_memory_map[SIZE_OF_BITMAP] = {0};
    void    *start_ptr = header->body.normal_size.fragments_start;
    for (int i = 0; i < BITMAP_LAST_INDEX; i++) {
        if (start_ptr == ptr) {
            set_bitmap(bitmap, false, i);

            return;
        }
    }
}


void free(void *ptr) {
    uintptr_t addr = (uintptr_t)ptr;
    uintptr_t page_start = addr & ~(0x1000 - 1);
    enum e_operation	op = FREE;


    struct s_header *header = (struct s_header *)page_start;
    if (header->size == TINY) {
        tiny_malloc(op);
    }
    print_sheader(header, 0);

    printf("%p", ptr);
}
