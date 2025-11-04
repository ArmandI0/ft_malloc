#include "../include/malloc.h"
#include <stdio.h>

void free_op(char *memory, struct s_bloc_header *ptr) {
	struct s_main_header	*main_header = (struct s_main_header *)memory;

	while (main_header != NULL) {
		if ((char *)main_header == ptr->head) {
			ptr->allocated = 0;
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
