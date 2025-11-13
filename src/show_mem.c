#include "../include/malloc.h"

static void print_byte_as_hex(unsigned char byte_value);
static void print_hex_offset(size_t offset);


void show_alloc_mem() {
	struct s_memory_operation	op;

	op.type = SHOW_MEMORY;

	tiny_malloc(&op);
	small_malloc(&op);
	large_malloc(&op);
}

void show_alloc_mem_ex() {
	struct s_memory_operation	op;

	op.type = SHOW_MEMORY_HEX;

	tiny_malloc(&op);
	small_malloc(&op);
	large_malloc(&op);
}

void show_mem_op(struct s_memory_operation *op) {
	size_t					nb_of_blocs;
	struct s_main_header	*main_header = (struct s_main_header *)op->memory;
	struct s_bloc_header	*bloc_header;
	size_t					count = 0;

	switch (main_header->size) {
		case TINY:
			ft_printf("TINY : \n");
			nb_of_blocs = NB_TINY_BLOCS;
			break;
		case SMALL:
			ft_printf("SMALL : \n");
			nb_of_blocs = NB_SMALL_BLOCS;
			break;
		default:
			ft_printf("LARGE : \n");
			nb_of_blocs = 1;
			break;
	}

	while (main_header) {
		bloc_header = (struct s_bloc_header *)((char *)main_header + HEADER_SIZE); // First bloc_header
		for (size_t i = 0; i < nb_of_blocs; i++)
		{
			if (bloc_header->allocated != 0) {
				void *start = (char *)bloc_header + HEADER_SIZE;
				void *end = (char *)start + bloc_header->allocated;
				ft_printf("%p - %p : %z \n", start, end, bloc_header->allocated);
				count++;
			}
			bloc_header = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + main_header->size);
		}
		main_header = (struct s_main_header *)main_header->next;
	}
	ft_printf("number of bloc : %z\n", count);
}

void show_mem_hex_op(struct s_memory_operation *op) {
	size_t					nb_of_blocs;
	struct s_main_header	*main_header = (struct s_main_header *)op->memory;
	struct s_bloc_header	*bloc_header;
	size_t					count = 0;

	switch (main_header->size) {
		case TINY:
			ft_printf("=== TINY ZONE HEX DUMP ===\n");
			nb_of_blocs = NB_TINY_BLOCS;
			break;
		case SMALL:
			ft_printf("=== SMALL ZONE HEX DUMP ===\n");
			nb_of_blocs = NB_SMALL_BLOCS;
			break;
		default:
			ft_printf("=== LARGE ZONE HEX DUMP ===\n");
			nb_of_blocs = 1;
			break;
	}

	while (main_header) {
		bloc_header = (struct s_bloc_header *)((char *)main_header + HEADER_SIZE);
		for (size_t i = 0; i < nb_of_blocs; i++)
		{
			if (bloc_header->allocated != 0) {
				void *start = (char *)bloc_header + HEADER_SIZE;
				ft_printf("\n--- Bloc %zu (Taille: %zu bytes, Addr: %p) ---\n", 
						 count, bloc_header->allocated, start);
				print_hexdump(start, bloc_header->allocated);
				count++;
			}
			bloc_header = (struct s_bloc_header *)((char *)bloc_header + HEADER_SIZE + main_header->size);
		}
		main_header = (struct s_main_header *)main_header->next;
	}
	
	if (count == 0) {
		ft_printf("Aucun bloc alloué dans cette zone.\n");
	} else {
		ft_printf("\nTotal: %zu bloc(s) avec contenu hexdump affiché.\n", count);
	}
}

void print_hexdump(const void *data, size_t size) {
    const unsigned char *p = (const unsigned char *)data;
    size_t i, j;

    if (data == NULL || size == 0) {
        ft_printf("Zone memoire vide ou taille nulle.\n");
        return;
    }

    ft_printf("--- Hex Dump de %z octets (Addr: %p) ---\n", size, data);
    ft_printf("Offset | 00 01 02 03 04 05 06 07 | 08 09 0A 0B 0C 0D 0E 0F | ASCII\n");
    ft_printf("-------+-------------------------+-------------------------+------------------\n");

    for (i = 0; i < size; i += 16) {
			print_hex_offset(i);        
		for (j = 0; j < 16; j++) {
            if (i + j < size) {
				print_byte_as_hex(p[i + j]);            
			} else {
                ft_printf("   ");
            }
            if (j == 7) {
                ft_printf("| ");
            }
        }
        ft_printf("| ");
        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                if (ft_isprint(p[i + j])) {
                    ft_printf("%c", p[i + j]);
                } else {
                    ft_printf(".");
                }
            } else {
                break;
            }
        }
        ft_printf("\n");
    }

    ft_printf("--------------------------------------------------------------------------------\n");
}

static void print_byte_as_hex(unsigned char byte_value) {
    const char 		hex_chars[] = "0123456789ABCDEF";
    unsigned char	high_nibble = (byte_value >> 4);
    unsigned char	low_nibble = (byte_value & 0x0F);

    ft_printf("%c", hex_chars[high_nibble]);
    ft_printf("%c", hex_chars[low_nibble]);
	ft_printf(" ");
}


static void print_hex_offset(size_t offset) {
    const char	hex_chars[] = "0123456789ABCDEF";
    char 		hex_representation[6]; 
    int			i;
    
    for (i = 5; i >= 0; i--) {
        hex_representation[i] = hex_chars[offset & 0x0F]; 
        offset >>= 4; 
    }
    for (i = 0; i < 6; i++) {
        ft_printf("%c", hex_representation[i]);
    }
    ft_printf(" | ");
}