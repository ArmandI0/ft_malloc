#include "../include/malloc.h"

char *verify_ptr(struct s_bloc_header *ptr) {
	struct s_memory_operation	op;
	char						*ptr_verify = NULL;

	op.type = VERIFY_PTR;
	op.free.ptr = ptr;
	ptr_verify = tiny_malloc(&op);
	if (ptr_verify) {
		return ptr_verify;
	}
	ptr_verify = small_malloc(&op);
	if (ptr_verify) {
		return ptr_verify;
	}
	ptr_verify = large_malloc(&op);
	return ptr_verify;
}

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
	if (verify_ptr(bloc_header) == NULL) {
		return;
	}

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
