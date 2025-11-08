#include "../include/malloc.h"

static char *do_operation(char *memory, struct s_memory_operation *op);

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
		default:
			ptr = NULL;
			break;
	}
	return ptr;
}