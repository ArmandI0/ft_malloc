#include "../include/malloc.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*source;
	unsigned char	*destination;
	size_t			i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	source = (unsigned char *) src;
	destination = (unsigned char *) dest;
	while (i < size)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			a;
	size_t			i;

	tmp = (unsigned char *) s;
	i = 0;
	a = c;
	while (i < n)
	{
		tmp[i] = a;
		i++;
	}
	return (s);
}

void print_bitmap(const char *bitmap, size_t size) {
    for (size_t i = 0; i < size; i++) {
        unsigned char byte = bitmap[i];
        for (int bit = 7; bit >= 0; bit--) { // du MSB au LSB
            printf("%d", (byte >> bit) & 1);
        }
        printf(" "); // espace entre chaque octet
    }
    printf("\n");
}

void set_bitmap(char *bitmap ,bool bit_val, int index) {
    int octet_idx = index / 8;
    int bit_idx   = 7 - (index % 8);	// MSB for debug

    if (bit_val)
        bitmap[octet_idx] |= (1 << bit_idx);
    else
        bitmap[octet_idx] &= ~(1 << bit_idx);
}

bool get_bitmap(const char *bitmap, int index) {
    int octet_idx = index / 8;
    int bit_idx   = 7 - (index % 8);	// MSB for debug

    return (bitmap[octet_idx] >> bit_idx) & 1;
}

