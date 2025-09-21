#ifndef malloc_h
#define malloc_h

#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h> // TODO  : a supprimer

#define TINY 16
#define SMALL 256
#define LARGE 1000

#define HEADER_SIZE 32
#define SIZE_OF_BITMAP 32
#define BITMAP_LAST_INDEX 256

enum e_operation {
	MALLOC,
	FREE,
	REALLOC,
};

// 32 octets
struct s_header_page {
	size_t	size_of_fragments;			// Taille d'un fragment
	int		free_fragments_remaining;	// Nb de fragments libre restant
	char	*fragments_start;			// Free fragment : Pointeur sur un fragment libre ou NULL si le bloc est rempli
	char	*next_page;					// Page memoire suivante si besoin
};

struct s_header_large_page {
	size_t	size;
	char	*previous_page;
	char	*next_page;
};


void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memset(void *s, int c, size_t n);
char 	*tiny_malloc(enum e_operation op);
void print_bitmap(const char *bitmap, size_t size);
void set_bitmap(char *bitmap ,bool bit_val, int index);
bool get_bitmap(const char *bitmap, int index);
char *init_tiny_map();
char *small_malloc(enum e_operation op);
char *init_small_map();
char *malloc_operation(char *memory, int fragment_size);
char *large_malloc(enum e_operation op, size_t size);


#endif