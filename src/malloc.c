#include "../include/malloc.h"

char *malloc_op(struct s_memory_operation *op) {
    struct s_main_header	*header = (struct s_main_header *)op->area->memory;
    struct s_bloc_header	*bloc_header;
    struct s_bloc_header	new_bloc_header;
    int                 	nb_of_blocs;
    char                	*ptr_allocated_bloc = NULL;

    switch (op->map_size) {
        case TINY_MAP:
            nb_of_blocs = NB_TINY_BLOCS;
            break;
        case SMALL_MAP:
            nb_of_blocs = NB_SMALL_BLOCS;
            break;
        case LARGE_MAP:
            nb_of_blocs = 1;
            break;
    }

    while (true) {
        bloc_header = (struct s_bloc_header *)((char *)header + HEADER_SIZE);

        for (int i = 0; i < nb_of_blocs; i++) { //find free bloc
            if (bloc_header->allocated == 0 && header->size >= op->malloc.size) { 
        		// Bloc allocation
                ptr_allocated_bloc = ((char*)bloc_header + HEADER_SIZE);
                bloc_header->allocated = op->malloc.size;

				// if the mmap area under init
                if ((char *)header == op->area->current_mmap_allocated) { 
                    
                    if (i != nb_of_blocs - 1) {
                        struct s_bloc_header *next_bloc = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + header->size);
                        
                        if (next_bloc >= op->area->maximum_allocated_ptr) {
                            new_bloc_header.allocated = 0;
                            new_bloc_header.head = (char *)header;
                            ft_memcpy(next_bloc, &new_bloc_header, sizeof(struct s_bloc_header)); 
                            op->area->maximum_allocated_ptr = (struct s_bloc_header *)((char *)next_bloc + HEADER_SIZE + header->size);
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
            
            if (op->map_size != LARGE_MAP) {
                struct s_main_header *new_header = (struct s_main_header *)tmp;
                op->area->current_mmap_allocated = tmp;
                op->area->maximum_allocated_ptr = (struct s_bloc_header *)(tmp + HEADER_SIZE + sizeof(struct s_bloc_header) + new_header->size);
        	}
        }
    }
}

void	*malloc(size_t size) {
	struct s_memory_operation	op;

	op.type = MALLOC;
	op.malloc.size = size;
    if (size == 0) {
        return NULL;
    }

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




