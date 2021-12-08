# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 19:41:09 by sel-melc          #+#    #+#              #
#    Updated: 2019/11/18 15:58:03 by sel-melc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = woody.c utils.c elf64.c
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

NAME = woody_woodpacker

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	$(CC) -fsanitize=address -o $(NAME) $(OBJ)  libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) $? -o $@

clean : 
	rm -f $(OBJ) libft/*.o
fclean :
	rm -f $(OBJ) $(NAME) woody libft/libft.a libft/*o

re : fclean all

.PHONY : clean fclean re all
