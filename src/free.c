#include "../include/malloc.h"

#include <stdio.h>

// void print_sheader(struct s_header *header, int is_large) {
//     if (!header) {
//         printf("Header is NULL\n");
//         return;
//     }

//     printf("Header at %p\n", (void*)header);
//     printf("Size: %zu bytes\n", header->size);

//     if (is_large) {
//         printf("Large page:\n");
//         printf("  Previous page: %p\n", (void*)header->body.large_size.previous_page);
//         printf("  Next page    : %p\n", (void*)header->body.large_size.next_page);
//     } else {
//         printf("Normal page:\n");
//         printf("  Free fragments remaining: %d\n", header->body.normal_size.free_fragments_remaining);
//         printf("  Fragments start         : %p\n", (void*)header->body.normal_size.fragments_start);
//         printf("  Next page               : %p\n", (void*)header->body.normal_size.next_page);
//     }
// }

// char *mask_empty_bitmap(char *bitmap_mask, int size) {
//     int nb_octets = BITMAP_LAST_INDEX / 8;

//     if (size == TINY) {
//         for (int i = 0; i < nb_octets; i++) {
//             if (i == 0) {
//                 bitmap_mask[i] = 0xC0;
//             }
//             else{
//                 bitmap_mask[i] = 0x00;
//             }
//         }
//     }
//     if (size == SMALL) {
//         for (int i = 0; i < nb_octets; i++) {
//             if (i % 2 == 0) {
//                 bitmap_mask[i] = 0x80;
//             }
//             else {
//                 bitmap_mask[i] = 0x00;
//             }
//         }
//     }
//     return NULL;
// }

// bool memory_is_empty(char *bitmap_mask, int size) {
//     int nb_octets = BITMAP_LAST_INDEX / 8;
//     bool is_empty = true;

//     if (size == TINY) {
//         for (int i = 0; i < nb_octets; i++) {
//             if (i == 0 && (unsigned char)bitmap_mask[i] != 0xC0) {
//                 return false;
//             }
//             else if (i > 0 && (unsigned char)bitmap_mask[i] != 0x00){
//                 return false;
//             }
//         }
//     }
//     else if (size == SMALL) {
//         for (int i = 0; i < nb_octets; i++) {
//             if (i % 2 == 0 && (unsigned char)bitmap_mask[i] != 0x80) {
//                 return false;
//             }
//             else if (i % 2 != 0 && (unsigned char)bitmap_mask[i] != 0x00) {
//                 return false;
//             }
//         }
//     }
//     return is_empty;
// }


// // Faire un filtre pour voir si la zone est vide
// void free_operation(struct s_header *header, void *ptr) {
//     char    *bitmap = (char *)(header + HEADER_SIZE);
//     void    *start_ptr = header;
//     size_t  size = header->size;

//     for (int i = 0; i < BITMAP_LAST_INDEX; i++) {
//         if (start_ptr == ptr) {
//             set_bitmap(bitmap, false, i);
//             if (memory_is_empty(bitmap, size) == true) {
//                 munmap(header, size * 256);
//             }
//             return;
//         }
//         start_ptr += size;
//     }
// }

void free_op(char *memory, struct s_bloc_header *ptr) {
	struct s_main_header	*main_header = (struct s_main_header *)memory;

	while (main_header != NULL) {
		if ((char *)main_header == ptr->head) {
			ptr->allocated = 0;
			return;
		}
		main_header = (struct s_main_header *)main_header->next;
	}
}

void free(void *ptr) {
	struct s_bloc_header 		*bloc_header;
	struct s_memory_operation	op;

    if (!ptr) {
        return;
	}

	op.type = FREE;
    bloc_header = (struct s_bloc_header *)((char *)ptr - HEADER_SIZE);
	op.ptr = bloc_header;
	
	if (bloc_header->allocated <= TINY) {
		tiny_malloc(&op);
	}
	else if (bloc_header->allocated <= SMALL) {
		small_malloc(&op);
	}
	else {
		large_malloc(&op);
	}
}
