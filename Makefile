# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 13:30:24 by moben-ta          #+#    #+#              #
#    Updated: 2025/06/17 11:22:03 by moben-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

CC = cc

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	READLINE_PREFIX := $(shell brew --prefix readline)
	CFLAGS += -I$(READLINE_PREFIX)/include
	LDFLAGS += -L$(READLINE_PREFIX)/lib -lreadline -lhistory
else
	CFLAGS += -I/usr/include/readline
	LDFLAGS += -lreadline
endif

NAME = minishell

SRCS = main.c \
	files/add_history.c files/check_pre_lexing_errors.c files/expand_segment_utils.c files/expand_segment.c files/ft_add_env.c \
	files/ft_add_tokens.c files/ft_create_tmp_env.c files/ft_exec_commands_utils1.c files/ft_exec_commands_utils2.c \
	files/ft_exec_commands_utils3.c files/ft_exec_commands_utils4.c files/ft_exec_commands.c files/ft_expand_utils.c \
	files/ft_expand_vars.c files/ft_expand_vars_utils.c files/ft_export_unset_utils.c files/ft_free.c files/ft_get_comands.c files/ft_get_comands_utils.c \
	files/ft_handle_redirct.c files/ft_init_data.c files/ft_isspecial_char.c \
	files/ft_lexer_util_1.c files/ft_lexer_util_2.c files/ft_lexer_util.c files/ft_lexer.c \
	files/ft_save_env.c files/ft_segment.c files/ft_signals.c files/herdoc.c files/print_banner.c \
	builtins/ft_builtin_export.c builtins/ft_builtin_exit.c builtins/ft_builtin_env.c builtins/ft_builtin_echo.c builtins/ft_builtin_cd.c \
	builtins/ft_builtin_pwd.c builtins/ft_builtin_unset.c builtins/ft_print_history.c

LBFT = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c \
	libft/ft_isdigit.c libft/ft_itoa.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c \
	libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c \
	libft/ft_split.c libft/ft_str_trim_n_cmp.c libft/ft_strchr.c libft/ft_strcmp.c libft/ft_strcpy.c \
	libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c \
	libft/ft_strncmp.c libft/ft_strncpy.c libft/ft_strndup.c libft/ft_strrchr.c libft/ft_strtrim.c \
	libft/ft_substr.c

GNL = get_next_line/get_next_line_utils.c get_next_line/get_next_line.c

OBJS = $(SRCS:.c=.o)
LBFTOBJS = $(LBFT:.c=.o)
GNLOBJ = $(GNL:.c=.o)

all: $(NAME)
	@echo "$(GREEN)✅ Done!$(RESET)"

$(NAME): $(OBJS) $(LBFTOBJS) $(GNLOBJ)
	@echo "$(YELLOW)📦 Compiling minishell...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LBFTOBJS) $(GNLOBJ) $(LDFLAGS) -o $(NAME)

files/%.o: files/%.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

builtins/%.o: builtins/%.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

libft/%.o: libft/%.c libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

get_next_line/%.o: get_next_line/%.c get_next_line/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LBFTOBJS) $(GNLOBJ)

fclean: clean
	rm -f $(NAME) .history_file

re: fclean all

.PHONY: all clean fclean re
