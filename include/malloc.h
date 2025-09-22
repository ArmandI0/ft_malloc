#ifndef malloc_h
#define malloc_h

#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h> // TODO  : a supprimer
#include <stdint.h>

#define TINY 128
#define NB_OF_TINY_BLOCS 199

#define SMALL 256
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

struct s_header_page {
	int		free_fragments_remaining;	// Nb de fragments libre restant
	char	*fragments_start;			// Free fragment : Pointeur sur un fragment libre ou NULL si le bloc est rempli
	char	*next_page;					// Page memoire suivante si besoin
};

struct s_header_large_page {
	char	*previous_page;
	char	*next_page;
};


struct s_header
{
	size_t	size;	// 8 octets
	union {			// 24 octets max
		struct s_header_page		normal_size;
		struct s_header_large_page	large_size;
	} body;
};
// 32 octets

struct s_main_header {	// 16 bytes
	size_t	size;
	char	*next;
};

struct s_bloc_header {	// 16 bytes
	uint8_t	allocated;
	char	*head;
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
char *mask_empty_bitmap(char *bitmap_mask, int size);
bool memory_is_empty(char *bitmap_mask, int size);


#endif