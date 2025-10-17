#include "../include/malloc.h"

static char *init_map(const size_t bloc_size) {
	char					*memory = NULL;
	int						page_size;
	struct s_main_header	header;
	struct s_bloc_header	bloc_header;

	// define size of mmap
	switch (bloc_size) {
		case TINY:
			page_size = sysconf(_SC_PAGESIZE) * NB_TINY_PAGE;
			break;
		case SMALL:
			page_size = sysconf(_SC_PAGESIZE) * NB_SMALL_PAGE;
			break;
		default:
			return NULL;
	}

	memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!memory) {
		return NULL;
	}

	// Init main header
	header.size = bloc_size;
	header.next = NULL;
	ft_memcpy(memory, &header, sizeof(struct s_main_header));

	//Init first bloc_header
	bloc_header.allocated = 0;
	bloc_header.head = memory;
	ft_memcpy(memory + HEADER_SIZE, &bloc_header, sizeof(struct s_bloc_header));
	return memory;
}

static char *malloc_op(const char *memory, const size_t bloc_size) {
	struct s_main_header	*header = (struct s_main_header *)memory;
	struct s_bloc_header	*bloc_header = (struct s_bloc_header *)((char *)memory + HEADER_SIZE);
	struct s_bloc_header	new_bloc_header;
	int						nb_of_blocs;
	char					*ptr_allocated_bloc = NULL;

	switch (bloc_size) {
		case TINY:
			nb_of_blocs = NB_TINY_BLOCS;
			break;
		case SMALL:
			nb_of_blocs = NB_SMALL_BLOCS;
			break;
		default:
			nb_of_blocs = 1;
	}

	while (true) {
		for (int i = 0; i < nb_of_blocs; i++) {	//find free bloc
			if (bloc_header->allocated == 0) {			// Bloc allocation
				ptr_allocated_bloc = ((char*)bloc_header + HEADER_SIZE);
				bloc_header->allocated = 1;
				// create a new header_bloc
				if (i != nb_of_blocs - 1) {
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
			char *tmp = init_map(bloc_size);
			if (tmp == NULL) {
				return NULL;
			}
			header->next = tmp;
			header = (struct s_main_header *)tmp;
			bloc_header = (struct s_bloc_header *)((char *)header + HEADER_SIZE);
		}
	}
}

static void show_mem(const char* memory, const size_t bloc_size) {
	size_t					nb_of_blocs;
	struct s_bloc_header	*bloc_header = (struct s_bloc_header *)((char *)memory + HEADER_SIZE); // First bloc_header

	switch (bloc_size) {
		case TINY:
			nb_of_blocs = NB_TINY_BLOCS;
			break;
		case SMALL:
			nb_of_blocs = NB_SMALL_BLOCS;
			break;
		default:
			nb_of_blocs = 1;
	}
	for (size_t i = 0; i < nb_of_blocs; i++)
	{
		if (bloc_header->allocated != 0) {
			ft_printf("%p \n", &bloc_header);
		}
	}
	
}


static char *tiny_malloc(enum e_operation op) {
	static char	*memory = NULL;

	if (memory == NULL) {
		memory = init_map(TINY);
		if (!memory)
			return NULL;
	}
	switch (op) {
		case MALLOC:
			return malloc_op(memory, TINY);
		case FREE:
			break;
		case SHOW_MEMORY:
			show_mem(memory, TINY);
			break;
		default:
			return NULL;
	}
	return NULL;
}

static char *small_malloc(enum e_operation op) {
	static char	*memory = NULL;

	if (memory == NULL) {
		memory = init_map(SMALL);
		if (!memory)
			return NULL;
	}
	switch (op) {
		case MALLOC:
			return malloc_op(memory, SMALL);
		case FREE:
			break;
		case SHOW_MEMORY:
			show_mem(memory, SMALL);
			break;
		default:
			return NULL;
	}
	return NULL;
}

static char *large_malloc(enum e_operation op, size_t size) {
	static char	*memory = NULL;

	if (memory == NULL) {
		memory = init_map(size);
		if (!memory)
			return NULL;
	}

	switch (op) {
		case MALLOC:
			return malloc_op(memory, size);
		case FREE:
			break;
		case SHOW_MEMORY:
			break;
		default:
			return NULL;
	}
	return NULL;
}

void	*malloc(size_t size) {
	enum e_operation	op = MALLOC;

	if (size <= TINY) {
		return tiny_malloc(op);
	}
	if (size <= SMALL) {
		return small_malloc(op);
	}
	else {
		return large_malloc(op, size);
	}
	return NULL;
}

void 	show_alloc_mem() {
	tiny_malloc(SHOW_MEMORY);
	small_malloc(SHOW_MEMORY);
}


