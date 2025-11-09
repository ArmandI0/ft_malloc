#include "../include/malloc.h"

void	*realloc_op(char *memory, struct s_bloc_header *ptr, size_t size) {
	struct s_main_header	*main_header = (struct s_main_header *)memory;
	void					*ptr_allocated_bloc = NULL;

	while (main_header != NULL) {
		if ((char *)main_header == ptr->head) {
			if (ptr->allocated < main_header->size) {
				ptr_allocated_bloc = ((char*)ptr + HEADER_SIZE);
				ptr->allocated = size;
				return ptr_allocated_bloc;
			}
			else {
				ptr->allocated = 0;
				return ptr_allocated_bloc = malloc(size);
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
	if (verify_ptr(bloc_header) == NULL) {
		return NULL;
	}
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
