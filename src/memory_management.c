#include "../includes/malloc.h"

static char *do_operation(struct s_memory_operation *op);

char *tiny_malloc(struct s_memory_operation *op) {
	static struct s_memory	tiny_area;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	op->map_size = TINY_MAP;
	op->area = &tiny_area;
	ptr = do_operation(op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

char *small_malloc(struct s_memory_operation *op) {
	static struct s_memory	small_area;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	op->map_size = SMALL_MAP;
	op->area = &small_area;
	ptr = do_operation(op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

char *large_malloc(struct s_memory_operation *op) {
	static struct s_memory	large_area;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	char					*ptr = NULL;

	pthread_mutex_lock(&lock);
	op->map_size = LARGE_MAP;
	op->area = &large_area;
	ptr = do_operation(op);
	pthread_mutex_unlock(&lock);
	return ptr;
}

static char *do_operation(struct s_memory_operation *op) {
	char *ptr = NULL;

	if (op->area->memory == NULL && op->type == MALLOC) {
		char *memory = init_map(op->malloc.size);
		if (!memory) {
			return NULL;
		}
		op->area->memory = memory;
		if (op->map_size != LARGE_MAP) {
        	struct s_main_header *header = (struct s_main_header *)memory;
        	op->area->current_mmap_allocated = memory;
        	op->area->maximum_allocated_ptr = (struct s_bloc_header *)(memory + HEADER_SIZE + sizeof(struct s_bloc_header) + header->size);
		}
		else {
			op->area->current_mmap_allocated = NULL;
			op->area->maximum_allocated_ptr = NULL;
		}
	}

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
	}
	return ptr;
}

char *init_map(const size_t bloc_size) {
	char					*memory = NULL;
	size_t					page_size;
	struct s_main_header	header;
	struct s_bloc_header	bloc_header;

	// define size of mmap
	if (bloc_size <= TINY) {
		page_size = sysconf(_SC_PAGESIZE) * NB_TINY_PAGE;
		header.size = TINY;
	}
	else if (bloc_size <= SMALL) {
		header.size = SMALL;
		page_size = sysconf(_SC_PAGESIZE) * NB_SMALL_PAGE;
	}
	else {
		header.size = bloc_size;
		page_size = bloc_size + HEADER_SIZE + HEADER_SIZE; // space for main_header + bloc_header
        if (bloc_size > page_size) {
            return NULL;
        }
	}

	memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (memory == MAP_FAILED) {
		return NULL;
	}
	// Init main header
	header.next = NULL;
	ft_memcpy(memory, &header, sizeof(struct s_main_header));

	//Init first bloc_header
	bloc_header.allocated = 0;
	bloc_header.head = memory;
	ft_memcpy(memory + HEADER_SIZE, &bloc_header, sizeof(struct s_bloc_header));

	return memory;
}