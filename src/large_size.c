#include "../include/malloc.h"

static char *init_large_map(size_t malloc_size) {
	char					    *memory = NULL;
	struct s_header_large_page	header;

	memory = mmap(NULL, malloc_size + HEADER_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!memory)
			return NULL;

	// Save header at the start of the new memory page
    header.previous_page = NULL;
	header.next_page = NULL;
	ft_memcpy(memory, &header, sizeof(struct s_header_large_page));
	return memory;
}


char *large_malloc(enum e_operation op, size_t size) {
	static char	*memory = NULL;

	if (op == MALLOC) {
        char *new_memory = init_large_map(size);
        if (memory == NULL) {
            memory = new_memory;
        }
        else {
            struct s_header_large_page	*new_header = (struct s_header_large_page*)new_memory;
            struct s_header_large_page	*header = (struct s_header_large_page*)memory;
            header->next_page = new_memory;
            new_header->previous_page = memory;
            memory = new_memory;
        }
		return new_memory + HEADER_SIZE;
	}
	return NULL;
}