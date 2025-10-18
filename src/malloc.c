#include "../include/malloc.h"

static char *init_map(const size_t bloc_size) {
	char					*memory = NULL;
	int						page_size;
	struct s_main_header	header;
	struct s_bloc_header	bloc_header;


	// define size of mmap
	if (bloc_size <= TINY) {
		page_size = sysconf(_SC_PAGESIZE) * NB_TINY_PAGE;
		header.size = TINY;
	}
	else if (bloc_size <= SMALL) {
		header.size = SMALL;
		page_size = sysconf(_SC_PAGESIZE) * NB_SMALL_PAGE;
	}
	else {
		header.size = bloc_size;
		page_size = bloc_size;
	}

	memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!memory) {
		return NULL;
	}
	// Init main header
	header.next = NULL;
	ft_memcpy(memory, &header, sizeof(struct s_main_header));

	//Init first bloc_header
	bloc_header.allocated = 0;
	bloc_header.head = memory;
	ft_memcpy(memory + HEADER_SIZE, &bloc_header, sizeof(struct s_bloc_header));





		// DEBUG ICI
	ft_printf("=== Dans init_map AVANT return ===\n");
	ft_printf("memory = %p\n", memory);
	struct s_bloc_header *check = (struct s_bloc_header *)(memory + HEADER_SIZE);
	ft_printf("check address = %p\n", check);
	ft_printf("check->allocated = %zu\n", check->allocated);
	ft_printf("check->head = %p\n", check->head);

	// Dump raw bytes
	ft_printf("Raw bytes at bloc_header:\n");
	unsigned char *bytes = (unsigned char *)(memory + HEADER_SIZE);
	for (int i = 0; i < 16; i++) {
		ft_printf("%02x ", bytes[i]);
	}
	ft_printf("\n");

	return memory;
}

static char *malloc_op(const char *memory, const size_t size) {
	struct s_main_header	*header = (struct s_main_header *)memory;
	struct s_bloc_header	*bloc_header = (struct s_bloc_header *)((char *)memory + HEADER_SIZE);
	struct s_bloc_header	new_bloc_header;
	int						nb_of_blocs;
	char					*ptr_allocated_bloc = NULL;

	if (size <= TINY) {
		nb_of_blocs = NB_TINY_BLOCS;
	}
	else if (size <= SMALL) {
		nb_of_blocs = NB_SMALL_BLOCS;
	}
	else {
		nb_of_blocs = 1;
	}
	ft_printf("=== Dans malloc_op DÉBUT ===\n");
	ft_printf("bloc_header->allocated = %zu\n", bloc_header->allocated);
	ft_printf("bloc_header->head = %p\n", bloc_header->head);

	// Dump raw bytes
	ft_printf("Raw bytes at bloc_header:\n");
	unsigned char *bytes = (unsigned char *)bloc_header;
	for (int i = 0; i < 16; i++) {
		ft_printf("%02x ", bytes[i]);
	}
	ft_printf("\n");
	while (true) {
		for (int i = 0; i < nb_of_blocs; i++) {	//find free bloc
			if (bloc_header->allocated == 0) {			// Bloc allocation
				ptr_allocated_bloc = ((char*)bloc_header + HEADER_SIZE);
				bloc_header->allocated = size;
				// create a new header_bloc
				if (i != nb_of_blocs - 1) {
					struct s_bloc_header *next_bloc = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + header->size);
					// Vérifier si le prochain bloc n'est pas déjà initialisé
					if (next_bloc->head != (char *)header) {
						new_bloc_header.allocated = 0;
						new_bloc_header.head = (char *)header;
						ft_memcpy(next_bloc, &new_bloc_header, sizeof(struct s_bloc_header));
					}
				}
				return ptr_allocated_bloc;
			}
			bloc_header = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + header->size);
		}
		if (header->next != NULL) {						// if another memory area are availaible
			header = (struct s_main_header *)header->next;
			bloc_header = (struct s_bloc_header *)((char *)header + HEADER_SIZE);
		}
		else {											// else create and allocate a new memory area
			char *tmp = init_map(size);
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
	struct s_main_header	*main_header = (struct s_main_header *)memory;
	struct s_bloc_header	*bloc_header;
	size_t					count = 0;

	switch (bloc_size) {
		case TINY:
			ft_printf("TINY : \n");
			nb_of_blocs = NB_TINY_BLOCS;
			break;
		case SMALL:
			ft_printf("SMALL : \n");
			nb_of_blocs = NB_SMALL_BLOCS;
			break;
		default:
			ft_printf("LARGE : \n");
			nb_of_blocs = 1;
			break;
	}

	while (main_header) {
		bloc_header = (struct s_bloc_header *)((char *)main_header + HEADER_SIZE); // First bloc_header
		for (size_t i = 0; i < nb_of_blocs; i++)
		{
			if (bloc_header->allocated != 0) {
				void *start = (char *)bloc_header + HEADER_SIZE;
				void *end = (char *)start + bloc_header->allocated;
				ft_printf("%p - %p : %z \n", start, end, bloc_header->allocated);
				count++;
			}
			bloc_header = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + bloc_size);
		}
		main_header = (struct s_main_header *)main_header->next;
	}
	ft_printf("number of bloc : %z\n", count);
}


static char *tiny_malloc(enum e_operation op, size_t size) {
	static char	*memory = NULL;

	if (memory == NULL) {
		memory = init_map(TINY);
		if (!memory)
			return NULL;
	}
	switch (op) {
		case MALLOC:
			return malloc_op(memory, size);
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

static char *small_malloc(enum e_operation op, size_t size) {
	static char	*memory = NULL;

	if (memory == NULL) {
		memory = init_map(SMALL);
		if (!memory)
			return NULL;
	}
	switch (op) {
		case MALLOC:
			return malloc_op(memory, size);
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
		return tiny_malloc(op, size);
	}
	if (size <= SMALL) {
		return small_malloc(op, size);
	}
	else {
		return large_malloc(op, size);
	}
	return NULL;
}

void 	show_alloc_mem() {
	tiny_malloc(SHOW_MEMORY, TINY);
	small_malloc(SHOW_MEMORY, SMALL);
}


