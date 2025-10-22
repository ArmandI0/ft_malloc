#ifndef malloc_h
#define malloc_h

#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h> // TODO  : a supprimer
#include <stdint.h>
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
	SHOW_MEMORY
};

struct s_main_header {	// 16 bytes
	size_t	size;
	char	*next;
}__attribute__((aligned(16)));

struct s_bloc_header {	// 16 bytes
	size_t	allocated;
	char	*head;
}__attribute__((aligned(16)));

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);	
void 	show_alloc_mem();
int		ft_print_size_t(size_t n);


#endif