#include "../include/malloc.h"

void free_op(struct s_memory_operation *op) {
	struct s_main_header	*main_header = (struct s_main_header *)op->memory;

	while (main_header != NULL) {
		if ((char *)main_header == op->free.ptr->head) {
			op->free.ptr->allocated = 0;
			return;
		}
		main_header = (struct s_main_header *)main_header->next;
	}
}

void free(void *ptr) {
	struct s_bloc_header 		*bloc_header;
	struct s_memory_operation	op;

    if (!ptr) {
        return;
	}

    bloc_header = (struct s_bloc_header *)((char *)ptr - HEADER_SIZE);
	op.type = FREE;
	op.free.ptr = bloc_header;
	
	if (bloc_header->allocated <= TINY) {
		tiny_malloc(&op);
	}
	else if (bloc_header->allocated <= SMALL) {
		small_malloc(&op);
	}
	else {
		large_malloc(&op);
	}
}
