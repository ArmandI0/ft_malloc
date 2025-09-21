#include "../include/malloc.h"


char *malloc_operation(char *memory, int fragment_size) {
	struct s_header			*header = (struct s_header *)memory;
	char					*next_memory_page = header->body.normal_size.next_page;
	char					*memory_page = memory;


	while (header)
	{
		print_bitmap(memory + HEADER_SIZE, 32);
		if (header->body.normal_size.free_fragments_remaining > 0) {
			for (int i = 0; i < BITMAP_LAST_INDEX; i++) {
				if (get_bitmap(memory_page + HEADER_SIZE, i) == false) {
					header->body.normal_size.free_fragments_remaining--;
					set_bitmap(memory_page + HEADER_SIZE, true, i);
					return header->body.normal_size.fragments_start + (fragment_size * i);
				}
			}
		}
		if (next_memory_page == NULL) {
			if (fragment_size == TINY) {
				header->body.normal_size.next_page = init_tiny_map();
			}
			else {
				header->body.normal_size.next_page = init_small_map();
			}
			if (header->body.normal_size.next_page == NULL) {
				return NULL;
			}
		}
		memory_page = header->body.normal_size.next_page;
		header = (struct s_header *)memory_page;
		next_memory_page = header->body.normal_size.next_page;
	}
	printf("CACA\n");
	return NULL;
}



void	*malloc(size_t size) {
	enum e_operation	op = MALLOC;

	if (size <= TINY) {
		return tiny_malloc(op);
	}
	else if (size <= SMALL) {
		return small_malloc(op);
	}
	else {
		return large_malloc(op, size);
	}
	return NULL;
}

