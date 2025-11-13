#include "../include/malloc.h"

static char *do_operation(struct s_memory_operation *op);

char *tiny_malloc(struct s_memory_operation *op) {
	static char				*memory = NULL;
	static struct 			s_bloc_header *maximum_allocated_ptr = NULL;	// Ptr to know if I have to allocate the next bloc
    static char 			*current_mmap_allocated = NULL; 				// Ptr to know if I have to allocate the next bloc
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	if (memory == NULL && op->type == MALLOC) {
		memory = init_map(TINY);
		if (!memory) {
			pthread_mutex_unlock(&lock);
			return NULL;
		}
        current_mmap_allocated = memory;
        struct s_main_header *header = (struct s_main_header *)memory;
        maximum_allocated_ptr = (struct s_bloc_header *)(memory + HEADER_SIZE + sizeof(struct s_bloc_header) + header->size);
	}
	op->memory = memory;
	op->current_mmap_allocated = &current_mmap_allocated;
	op->maximum_allocated_ptr = &maximum_allocated_ptr;

	ptr = do_operation(op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

char *small_malloc(struct s_memory_operation *op) {
	static char				*memory = NULL;
	static struct 			s_bloc_header *maximum_allocated_ptr = NULL;	// Ptr to know if I have to allocate the next bloc
    static char 			*current_mmap_allocated = NULL; 				// Ptr to know if I have to allocate the next bloc
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	if (memory == NULL && op->type == MALLOC) {
		memory = init_map(SMALL);
		if (!memory) {
			pthread_mutex_unlock(&lock);
			return NULL;
		}
        current_mmap_allocated = memory;
        struct s_main_header *header = (struct s_main_header *)memory;
        maximum_allocated_ptr = (struct s_bloc_header *)(memory + HEADER_SIZE + sizeof(struct s_bloc_header) + header->size);
	}
	op->memory = memory;
	op->current_mmap_allocated = &current_mmap_allocated;
	op->maximum_allocated_ptr = &maximum_allocated_ptr;

	ptr = do_operation(op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

char *large_malloc(struct s_memory_operation *op) {
	static char				*memory = NULL;
	static struct 			s_bloc_header *maximum_allocated_ptr = NULL;	// Ptr to know if I have to allocate the next bloc
    static char 			*current_mmap_allocated = NULL; 				// Ptr to know if I have to allocate the next bloc
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	if (memory == NULL && op->type == MALLOC) {
		memory = init_map(op->malloc.size);
		if (!memory) {
			pthread_mutex_unlock(&lock);
			return NULL;
		}
        current_mmap_allocated = memory;
        struct s_main_header *header = (struct s_main_header *)memory;
        maximum_allocated_ptr = (struct s_bloc_header *)(memory + HEADER_SIZE + sizeof(struct s_bloc_header) + header->size);
	}
	op->memory = memory;
	op->current_mmap_allocated = &current_mmap_allocated;
	op->maximum_allocated_ptr = &maximum_allocated_ptr;

	ptr = do_operation(op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

static char *do_operation(struct s_memory_operation *op) {
	char *ptr = NULL;

	switch (op->type) {
		case MALLOC:
			ptr = malloc_op(op);
			break;
		case FREE:
			free_op(op);
			break;
		case SHOW_MEMORY:
			show_mem_op(op);
			break;
		case REALLOC:
			ptr = realloc_op(op);
			break;
		case SHOW_MEMORY_HEX:
			show_mem_hex_op(op);
			break;
		default:
			ptr = NULL;
			break;
	}
	return ptr;
}
