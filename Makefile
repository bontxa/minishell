# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltombell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 12:45:42 by aboncine          #+#    #+#              #
#    Updated: 2023/01/30 16:38:28 by ltombell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c execute_cmd.c variable_parser.c utils.c utils2.c utils3.c \
	parse_and_split.c ft_split.c special_chars.c check_for_minus.c here_doc.c \
	get_next_line.c get_next_line_utils.c create_and_add_elem.c ft_itoa.c altro_split.c \
	gestione_virgo.c arr_utils.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

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
