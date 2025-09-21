#include "../include/malloc.h"


static void *init_new_map() {
	void					*memory = NULL;
	int						page_size = getpagesize();
	struct s_header_page	header;

	memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!memory)
			return NULL;
	header.free_fragments_remaining = page_size / TINY - 1;
	header.free_fragment = &memory[TINY];
	ft_memcpy(memory, &header, sizeof(struct s_header_page));
	return memory;
}

static void tiny_malloc(enum e_operation op) {
	static void				*memory = NULL;

	if (!memory) {
		memory = init_new_map();
		if (!memory)
			return NULL;
	}
	struct s_header_page *header = (struct s_header_page *)memory;
	if (header->free_fragments_remaining > 0) {
		void	*malloc_ptr = header->free_fragment;
		header->free_fragments_remaining--;
		if (header->free_fragments_remaining > 0) {
			header->free_fragment = (void*)((char*)header->free_fragment + TINY);
		}
		else {
			header->free_fragment = NULL;
		}
	}
	else {
		// Rajouter des pages
	}
}

void	*malloc(size_t size) {
	enum e_operation	op = MALLOC;

	if (size <= TINY) {
		tiny_malloc(op);
	}
}

