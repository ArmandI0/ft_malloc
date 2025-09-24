#ifndef malloc_h
#define malloc_h

#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h> // TODO  : a supprimer
#include <stdint.h>

// #define TINY 128
// #define	NB_TINY_PAGE 7
// #define NB_TINY_BLOCS 199

#define TINY 1024
#define	NB_TINY_PAGE 146
#define NB_TINY_BLOCS 575

#define SMALL 1024
#define	NB_SMALL_PAGE 146
#define NB_SMALL_BLOCS 575

#define SMALL 1024
#define LARGE 1000

#define HEADER_SIZE 16
#define SIZE_OF_BITMAP 32
#define BITMAP_LAST_INDEX 256
#define PAGE_SIZE 4096

enum e_operation {
	MALLOC,
	FREE,
	REALLOC,
};

struct s_main_header {	// 16 bytes
	size_t	size;
	char	*next;
};

struct s_bloc_header {	// 16 bytes
	uint8_t	allocated;
	char	*head;
};

struct test{
	struct s_main_header	a;
	struct s_bloc_header 	b;
};

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memset(void *s, int c, size_t n);

#endif