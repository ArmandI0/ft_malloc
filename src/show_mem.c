#include "../include/malloc.h"

void show_alloc_mem() {
	struct s_memory_operation	op;

	op.type = SHOW_MEMORY;

	tiny_malloc(&op);
	small_malloc(&op);
	large_malloc(&op);
}

// void show_alloc_mem_ex() {
// 	struct s_memory_operation	op;

// }

void show_mem_op(const char* memory) {
	size_t					nb_of_blocs;
	struct s_main_header	*main_header = (struct s_main_header *)memory;
	struct s_bloc_header	*bloc_header;
	size_t					count = 0;

	switch (main_header->size) {
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
			bloc_header = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + main_header->size);
		}
		main_header = (struct s_main_header *)main_header->next;
	}
	ft_printf("number of bloc : %z\n", count);
}