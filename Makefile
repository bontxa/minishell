# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboncine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 12:45:42 by aboncine          #+#    #+#              #
#    Updated: 2023/02/09 12:26:32 by aboncine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c execute_cmd.c variable_parser.c utils.c utils2.c utils3.c \
	parse_and_split.c ft_split.c special_chars.c check_for_minus.c here_doc.c \
	get_next_line.c get_next_line_utils.c create_and_add_elem.c utils4.c \
	altro_split.c gestione_virgo.c arr_utils.c executer.c export_var.c \
	exit_status.c print_functions.c builtins.c signals_and_vars.c \
	variable_parser_2.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) -c $(CFLAGS) $?

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re .c.o
