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