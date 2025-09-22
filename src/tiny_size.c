#include "../include/malloc.h"

char *init_tiny_map() {
	char					*memory = NULL;
	int						page_size = getpagesize();
	struct s_main_header	header;
	struct s_bloc_header	bloc_header;

	memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!memory)
			return NULL;

	// Init main header
	header.size = TINY;
	header.next = NULL;
	ft_memcpy(memory, &header, sizeof(struct s_header));

	//Init first bloc_header
	bloc_header.allocated = 0;
	bloc_header.head = memory;
	return memory;
}

char *tiny_malloc(enum e_operation op) {
	static char	*memory = NULL;

	if (!memory) {
		memory = init_tiny_map();
		if (!memory)
			return NULL;
	}
	if (op == MALLOC) {
		char *malloc_ptr = malloc_operation(memory, TINY);
		return malloc_ptr;
	}
	if (op == FREE) {
		
	}
	return NULL;
}