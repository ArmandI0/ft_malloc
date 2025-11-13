#include "../include/malloc.h"

char *init_map(const size_t bloc_size) {
	char					*memory = NULL;
	int						page_size;
	struct s_main_header	header;
	struct s_bloc_header	bloc_header;

	ft_printf("INIT MAP %d \n", bloc_size);

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
		page_size = bloc_size + HEADER_SIZE + HEADER_SIZE; // space for main_header + bloc_header
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

	return memory;
}

char *malloc_op(struct s_memory_operation *op) {
    struct s_main_header	*header = (struct s_main_header *)op->memory;
    struct s_bloc_header	*bloc_header;
    struct s_bloc_header	new_bloc_header;
    int                 	nb_of_blocs;
    char                	*ptr_allocated_bloc = NULL;
	struct s_bloc_header 	**maximum_allocated_ptr = op->maximum_allocated_ptr;
    char                 	**current_mmap_allocated = op->current_mmap_allocated;

    if (op->malloc.size <= TINY) {
        nb_of_blocs = NB_TINY_BLOCS;
    }
    else if (op->malloc.size <= SMALL) {
        nb_of_blocs = NB_SMALL_BLOCS;
    }
    else {
        nb_of_blocs = 1;
    }

    while (true) {
        bloc_header = (struct s_bloc_header *)((char *)header + HEADER_SIZE);

        for (int i = 0; i < nb_of_blocs; i++) { //find free bloc
            if (bloc_header->allocated == 0 && header->size >= op->malloc.size) { 
        		// Bloc allocation
                ptr_allocated_bloc = ((char*)bloc_header + HEADER_SIZE);
                bloc_header->allocated = op->malloc.size;

				// if the mmap area under init
                if ((char *)header == *current_mmap_allocated) { 
                    
                    if (i != nb_of_blocs - 1) {
                        struct s_bloc_header *next_bloc = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + header->size);
                        
                        if (next_bloc >= *maximum_allocated_ptr) {
                            new_bloc_header.allocated = 0;
                            new_bloc_header.head = (char *)header;
                            ft_memcpy(next_bloc, &new_bloc_header, sizeof(struct s_bloc_header)); 
                            *maximum_allocated_ptr = (struct s_bloc_header *)((char *)next_bloc + HEADER_SIZE + header->size);
                        }
                    }
                }
                return ptr_allocated_bloc;
            }
            bloc_header = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + header->size);
        }
        if (header->next != NULL) {
            header = (struct s_main_header *)header->next;
        }
        else {
            char *tmp = init_map(op->malloc.size);
            if (tmp == NULL) {
                return NULL;
            }
            header->next = tmp;
            header = (struct s_main_header *)tmp;
            
            *current_mmap_allocated = tmp;
            struct s_main_header *new_header = (struct s_main_header *)tmp;
            *maximum_allocated_ptr = (struct s_bloc_header *)(tmp + HEADER_SIZE + sizeof(struct s_bloc_header) + new_header->size);
        }
    }
}

void	*malloc(size_t size) {
	struct s_memory_operation	op;

	op.type = MALLOC;
	op.malloc.size = size;

	if (size <= TINY) {
		return tiny_malloc(&op);
	}
	else if (size <= SMALL) {
		return small_malloc(&op);
	}
	else {
		return large_malloc(&op);
	}
	return NULL;
}




