#ifndef __malloc.h__
#define __malloc.h__

#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>

#define TINY 32
#define SMALL 128
#define LARGE 1000



enum e_operation {
	MALLOC,
	FREE,
	REALLOC,
};	

struct s_header_page
{
	size_t					size_of_fragments;			// Taille d'un fragment
	int						free_fragments_remaining;	// Nb de fragments libre restant
	void					*free_fragment;				// Free fragment : Pointeur sur un fragment libre ou NULL si le bloc est rempli
	struct s_header_page	*next_page;					// Page memoire suivante si besoin
};


void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t size);


#endif