# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: armandanger <armandanger@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 11:13:31 by aranger           #+#    #+#              #
#    Updated: 2025/10/26 22:22:31 by armandanger      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_isdigit.c \
			ft_bzero.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_atoi.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strrchr.c \
			ft_strchr.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_count_word.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_striteri.c \
			ft_printf/ft_print_adress.c \
			ft_printf/ft_print_others.c \
			ft_printf/ft_print_unsigned.c \
			ft_printf/ft_printf.c \

SRC			= $(addprefix src/, $(SRCS))

OBJS		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
D_OBJS		= mkdir -p $(@D)

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
NAME 		= libft.a

RM 			= rm -f
RM_OBJ		= rm -rf
AR 			= ar -rcs

#-RULES-#

all: 			${NAME}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@$(D_OBJS)
				$(CC) $(CFLAGS) -c -o $@ $<

${NAME}: 		${OBJS}
				${AR} ${NAME} ${OBJS}

clean:
				${RM_OBJ} ${OBJ_DIR}

fclean: 		clean
				${RM} ${NAME}

re:				fclean all

.PHONY : 		all clean fclean re 