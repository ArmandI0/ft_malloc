#include "../includes/malloc.h"

void free_op(struct s_memory_operation *op) {
	struct s_main_header	*main_header = (struct s_main_header *)op->area->memory;
	struct s_main_header	*prev_header = NULL;

	if (!main_header) {
		return;
	}

	while (main_header != NULL) {
		if ((char *)main_header == op->free.ptr->head) {
			if (op->map_size == LARGE_MAP) {
				if (prev_header) {
					prev_header->next = main_header->next;
				} else {
					op->area->memory = main_header->next;
				}
				munmap(main_header, main_header->size + HEADER_SIZE + HEADER_SIZE);
			} else {
				op->free.ptr->allocated = 0;
			}
			return;
		}
		prev_header = main_header;
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
