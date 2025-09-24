#include "../include/malloc.h"

// char *init_small_map() {
// 	char					*memory = NULL;
// 	int						page_size = getpagesize() * 16;
// 	struct s_header			header;
// 	struct s_header			header_page;
// 	char					bit_memory_map[SIZE_OF_BITMAP] = {0};

// 	memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
// 	if (!memory)
// 			return NULL;

// 	// Save header at the start of the new memory page
// 	header.size = SMALL;
// 	header.body.normal_size.free_fragments_remaining = page_size / SMALL - 1;
// 	header.body.normal_size.fragments_start = memory + SMALL;
// 	header.body.normal_size.next_page = NULL;
// 	ft_memcpy(memory, &header, sizeof(struct s_header));

// 	// Header for pages, to find the start of memory area
// 	header_page.size = SMALL;
// 	header_page.body.normal_size.free_fragments_remaining = -1;
// 	header_page.body.normal_size.fragments_start = memory + SMALL;
// 	header_page.body.normal_size.next_page = NULL;

// 	// Save bitmap after header [header 32octets][bitmap 32octets][n fragements of 16octets]
// 	set_bitmap(bit_memory_map, true, 0);
// 	ft_memcpy(memory + HEADER_SIZE, bit_memory_map, SIZE_OF_BITMAP);

// 	for (int i = 1; i < 16; i++) {
// 		ft_memcpy(memory + (PAGE_SIZE * i), &header_page, sizeof(struct s_header));
// 		set_bitmap(bit_memory_map, true, i * 16);
// 		header.body.normal_size.free_fragments_remaining--;
// 	}

// 	return memory;
// }

char *small_malloc(enum e_operation op) {
	static char	*memory = NULL;

	if (!memory) {
		// memory = init_small_map();
		if (!memory)
			return NULL;
	}
	if (op == MALLOC) {
		// char *malloc_ptr = malloc_op(memory, SMALL);
		// return malloc_ptr;
	}
	return NULL;
}