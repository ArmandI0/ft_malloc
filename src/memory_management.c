#include "../include/malloc.h"

static char *do_operation(char *memory, struct s_memory_operation *op);
static char *verify_ptr_op(char *memory, struct s_bloc_header *ptr_to_find);

char *tiny_malloc(struct s_memory_operation *op) {
	static char				*memory = NULL;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	if (memory == NULL) {
		memory = init_map(TINY);
		if (!memory) {
			pthread_mutex_unlock(&lock);
			return NULL;
		}
	}

	ptr = do_operation(memory, op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

char *small_malloc(struct s_memory_operation *op) {
	static char				*memory = NULL;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	if (memory == NULL) {
		memory = init_map(SMALL);
		if (!memory) {
			pthread_mutex_unlock(&lock);
			return NULL;
		}
	}

	ptr = do_operation(memory, op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

char *large_malloc(struct s_memory_operation *op) {
	static char				*memory = NULL;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	if (memory == NULL) {
		memory = init_map(op->malloc.size);
		if (!memory) {
			pthread_mutex_unlock(&lock);
			return NULL;
		}
	}

	ptr = do_operation(memory, op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

static char *do_operation(char *memory, struct s_memory_operation *op) {
	char *ptr = NULL;

	switch (op->type) {
		case MALLOC:
			ptr = malloc_op(memory, op->malloc.size);
			break;
		case FREE:
			free_op(memory, op->free.ptr);
			break;
		case SHOW_MEMORY:
			show_mem_op(memory);
			break;
		case REALLOC:
			ptr = realloc_op(memory, op->realloc.ptr, op->realloc.size);
			break;
		case SHOW_MEMORY_HEX:
			show_mem_hex_op(memory);
			break;
		case VERIFY_PTR:
			ptr = verify_ptr_op(memory, op->free.ptr);
			break;
		default:
			ptr = NULL;
			break;
	}
	return ptr;
}

static char *verify_ptr_op(char *memory, struct s_bloc_header *ptr_to_find) {
	struct s_main_header	*main_header = (struct s_main_header *)memory;
	
    if (!memory) {
		return 0;
	}
	while (main_header != NULL) {
        char *page_start = (char *)main_header;

        if (ptr_to_find->head == page_start) {
            return (char *)ptr_to_find;
        }
		main_header = (struct s_main_header *)main_header->next;
	}

    return NULL;
}