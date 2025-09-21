#include "../include/malloc.h"

char *init_small_map() {
	char					*memory = NULL;
	int						page_size = getpagesize() * 16;
	struct s_header_page	header;
	char					bit_memory_map[SIZE_OF_BITMAP] = {0};

	memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!memory)
			return NULL;

	// Save header at the start of the new memory page
	header.free_fragments_remaining = page_size / SMALL - 1;
	header.fragments_start = memory + SMALL;
	header.next_page = NULL;
	ft_memcpy(memory, &header, sizeof(struct s_header_page));

	// Save bitmap after header [header 32octets][bitmap 32octets][n fragements of 16octets]
	set_bitmap(bit_memory_map, true, 0);
	ft_memcpy(memory + HEADER_SIZE, bit_memory_map, SIZE_OF_BITMAP);
	return memory;
}

char *small_malloc(enum e_operation op) {
	static char	*memory = NULL;

	if (!memory) {
		memory = init_small_map();
		if (!memory)
			return NULL;
	}
	if (op == MALLOC) {
		char *malloc_ptr = malloc_operation(memory, SMALL);
		return malloc_ptr;
	}
	return NULL;
}