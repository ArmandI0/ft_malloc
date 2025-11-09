
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#-PATH FILES-#

SRC_DIR			= src
OBJ_DIR			= obj

#-LIBFT-#

LIBFT			= lib/libft
LIBFT_A			= $(LIBFT)/libft.a

SRCS			= \
				malloc.c \
				free.c \
				realloc.c \
				memory_management.c \
				show_mem.c \
				
SRC				= $(addprefix src/, $(SRCS))
OBJS			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
D_OBJS			= mkdir -p $(@D)



#-UTILS-#

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g -fPIC
NAME 			= libft_malloc_$(HOSTTYPE).so
RM 				= rm -f
RMR				= rm -rf

#-RULES-#

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
				@make -C $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): 		$(OBJS)
				@$(CC) $(CFLAGS) -shared $(OBJS) $(LIBFT_A) -o $(NAME)
				
clean:
				@$(RMR) $(OBJ_DIR)
				@make -C $(LIBFT) clean

fclean: 		clean
				@$(RM) $(NAME)
				@make -C $(LIBFT) fclean

re:				fclean all

.PHONY : 		all clean fclean re bonus