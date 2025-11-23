#include "../includes/malloc.h"

static enum e_map_size define_size_area(size_t size);

void	*realloc_op(struct s_memory_operation *op) {
	struct s_main_header	*main_header = (struct s_main_header *)op->area->memory;
	struct s_bloc_header	*ptr_to_realloc = op->realloc.ptr;
	enum e_map_size			realloc_size_map = define_size_area(op->realloc.size);
	void					*ptr_allocated_bloc = NULL;
	void					*old_ptr = NULL;

	if (!main_header) {
		return NULL;
	}

	while (main_header != NULL) {
		if ((char *)main_header == ptr_to_realloc->head) {
			if (op->realloc.size <= main_header->size && realloc_size_map == op->map_size) {
				ptr_allocated_bloc = ((char*)ptr_to_realloc + HEADER_SIZE);
				ptr_to_realloc->allocated = op->realloc.size;
				return ptr_allocated_bloc;
			}
			else {
				if (op->map_size == LARGE_MAP && realloc_size_map == LARGE_MAP) {
					op->type = MALLOC;
					op->malloc.size = op->realloc.size;
					ptr_allocated_bloc = malloc_op(op);
				}
				else {
					ptr_allocated_bloc = malloc(op->realloc.size);
				}
				if (ptr_allocated_bloc == NULL) {
                    return NULL;
                }
				old_ptr = (void*)((char*)ptr_to_realloc + HEADER_SIZE);
				ft_memcpy(ptr_allocated_bloc, old_ptr, ptr_to_realloc->allocated);
				ptr_to_realloc->allocated = 0; // free bloc
				return ptr_allocated_bloc;
			}
		}
		main_header = (struct s_main_header *)main_header->next;
	}
	return ptr_allocated_bloc;
}


void	*realloc(void *ptr, size_t size) {
	struct s_bloc_header 		*bloc_header;
	struct s_memory_operation	op;

    if (!ptr) {
        return NULL;
	}

    bloc_header = (struct s_bloc_header *)((char *)ptr - HEADER_SIZE);
	op.type = REALLOC;
	op.realloc.ptr = bloc_header;
	op.realloc.size = size;

	if (bloc_header->allocated <= TINY) {
		return tiny_malloc(&op);
	}
	else if (bloc_header->allocated <= SMALL) {
		return small_malloc(&op);
	}
	else {
		return large_malloc(&op);
	}
}


static enum e_map_size define_size_area(size_t size) {
	if (size <= TINY) {
		return TINY_MAP;
	}
	else if (size <= SMALL) {
		return SMALL_MAP;
	}
	else {
		return LARGE_MAP;
	}
}
