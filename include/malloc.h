#ifndef malloc_h
#define malloc_h

#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include "../lib/libft/src/libft.h"

#define TINY 128
#define	NB_TINY_PAGE 16
#define NB_TINY_BLOCS 455

#define SMALL 1024
#define	NB_SMALL_PAGE 146
#define NB_SMALL_BLOCS 575

#define HEADER_SIZE 16
#define SIZE_OF_BITMAP 32
#define BITMAP_LAST_INDEX 256
#define PAGE_SIZE 4096

enum e_operation {
	MALLOC,
	FREE,
	REALLOC,
	SHOW_MEMORY,
	SHOW_MEMORY_HEX,
};

struct s_main_header {	// 16 bytes
	size_t	size;
	char	*next;
}__attribute__((aligned(16)));

struct s_bloc_header {	// 16 bytes
	size_t	allocated;
	char	*head;
}__attribute__((aligned(16)));

struct s_free {
	struct s_bloc_header	*ptr;
};

struct s_malloc {
	size_t	size;
};

struct s_realloc {
	struct s_bloc_header	*ptr;
	size_t					size;
};

struct s_memory_operation {
	enum e_operation		type;
	union {
		struct s_malloc		malloc;
		struct s_free		free;
		struct s_realloc	realloc;
	};
};

char 	*init_map(const size_t bloc_size);
void	*malloc(size_t size);
char 	*malloc_op(const char *memory, const size_t size);
void	free(void *ptr);
void 	free_op(char *memory, struct s_bloc_header *ptr);
void	*realloc(void *ptr, size_t size);
void	*realloc_op(char *memory, struct s_bloc_header *ptr, size_t size);
void 	show_alloc_mem();
void	show_alloc_mem_ex();
void 	show_mem_op(const char* memory);
void 	print_hexdump(const void *data, size_t size);

char 	*tiny_malloc(struct s_memory_operation *op);
char 	*small_malloc(struct s_memory_operation *op);
char 	*large_malloc(struct s_memory_operation *op);

#endif