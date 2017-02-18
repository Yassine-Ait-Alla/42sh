# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaitalla <yaitalla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/30 01:29:56 by yaitalla          #+#    #+#              #
#    Updated: 2016/07/15 14:19:30 by yaitalla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=21sh
CFLAGS=-Werror -Wextra -Wall -Ilibft/includes
LFLAGS=-Llibft -lft
SRC=main.c prompt.c termcap.c init.c hash.c func.c lexer.c parse_error.c \
	process.c proc.c error.c built_func.c file.c environ.c builtin.c exit.c \
	forest.c abstract_syntax.c binary_tree.c tokenizer.c key.c cursor_manage.c \
	regulate.c historic.c sig_manager.c cursor_func.c display.c normal.c \
	prompter.c misc.c lex.c hdocs.c
OBJ=$(SRC:.c=.o)

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^ $(LFLAGS) -ltermcap

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

lib:
	make -C libft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

.PHONY: clean fclean all

re: fclean all
