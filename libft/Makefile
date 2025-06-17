# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 10:38:31 by moben-ta          #+#    #+#              #
#    Updated: 2025/06/05 12:34:38 by moben-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRC = ft_substr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_strlen.c ft_strcpy.c ft_strchr.c \
	ft_strrchr.c ft_atoi.c ft_strncmp.c \
	ft_memset.c ft_bzero.c ft_memmove.c \
	ft_memcmp.c ft_memchr.c ft_memcpy.c ft_calloc.c \
	ft_str_trim_n_cmp.c ft_strlcat.c ft_strjoin.c ft_strtrim.c \
	ft_strdup.c ft_split.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_itoa.c ft_strlcpy.c ft_strcmp.c \
	ft_strndup.c ft_strncpy.c

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	ar rcs ${NAME} ${OBJ}

%.o:%.c libft.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY : clean
