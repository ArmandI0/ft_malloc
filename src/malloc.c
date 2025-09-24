#include "../include/malloc.h"

static char *init_map() {
	char					*memory = NULL;
	int						page_size = getpagesize() * NB_TINY_PAGE;
	struct s_main_header	header;
	struct s_bloc_header	bloc_header;

	memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!memory)
			return NULL;
	struct test	test;

	// Init main header
	header.size = TINY;
	header.next = NULL;
	// ft_memcpy(memory, &header, sizeof(struct s_main_header));

	//Init first bloc_header
	bloc_header.allocated = 0;
	bloc_header.head = memory;
	// ft_memcpy(memory + HEADER_SIZE, &bloc_header, sizeof(struct s_bloc_header));
	test.a = header;
	test.b = bloc_header;
	ft_memcpy(memory, &test, sizeof(struct test));

	return memory;
}

static char *malloc_op(const char *memory, const int bloc_size) {
	struct s_main_header	*header = (struct s_main_header *)memory;
	struct s_bloc_header	*bloc_header = (struct s_bloc_header *)((char *)memory + HEADER_SIZE);
	struct s_bloc_header	new_bloc_header;
	char					*ptr_allocated_bloc = NULL;

	while (true) {
		for (int i = 0; i < NB_TINY_BLOCS; i++) {	//find free bloc
			if (bloc_header->allocated == 0) {			// Bloc allocation
				ptr_allocated_bloc = ((char*)bloc_header + HEADER_SIZE);
				bloc_header->allocated = 1;
				// create a new header_bloc
				if (i != NB_TINY_BLOCS - 1) {
					new_bloc_header.allocated = 0;
					new_bloc_header.head = (char *)header;
					ft_memcpy(ptr_allocated_bloc + bloc_size, &new_bloc_header, sizeof(struct s_bloc_header));
				}
				return ptr_allocated_bloc;
			}
			bloc_header = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + bloc_size);		// Incrementation of ptr to the next header_bloc
		}
		if (header->next != NULL) {						// if another memory area are availaible
			header = (struct s_main_header *)header->next;
			bloc_header = (struct s_bloc_header *)((char *)header + HEADER_SIZE);
		}
		else {											// else create and allocate a new memory area
			char *tmp = init_map();
			if (tmp == NULL) {
				return NULL;
			}
			header->next = tmp;
			header = (struct s_main_header *)tmp;
			bloc_header = (struct s_bloc_header *)((char *)header + HEADER_SIZE);
		}
	}
}


static char *tiny_malloc(enum e_operation op) {
	static char	*memory = NULL;

	if (memory == NULL) {
		memory = init_map();
		if (!memory)
			return NULL;
	}
	if (op == MALLOC) {
		char *malloc_ptr = malloc_op(memory, TINY);
		return malloc_ptr;
	}
	if (op == FREE) {
		
	}
	return NULL;
}


void	*malloc(size_t size) {
	enum e_operation	op = MALLOC;

	if (size <= TINY) {
		return tiny_malloc(op);
	}
	return NULL;
}

