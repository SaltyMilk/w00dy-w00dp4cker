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

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
SRC = woody.c utils.c elf64.c elf32.c
endif
ifeq ($(UNAME), Darwin)
SRC = macho_woody.c utils.c mach64.c
endif

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o) 

NAME = woody_woodpacker

all : $(NAME)

$(NAME) : $(OBJ) encryption/encrypt.o
	make -C libft
	$(CC) -o $(NAME) $(OBJ)  encryption/encrypt.o libft/libft.a


ifeq ($(UNAME), Linux)
encryption/encrypt.o: encryption/encrypt.s
	nasm -felf64 encryption/encrypt.s -o encryption/encrypt.o
endif

ifeq ($(UNAME), Darwin)
encryption/encrypt.o: encryption/encrypt.s
	nasm -fmacho64 encryption/encrypt.s -o encryption/encrypt.o
endif

%.o: %.c
	$(CC) $(CFLAGS) $? -o $@

clean : 
	rm -f $(OBJ) libft/*.o encryption/encrypt.o
fclean :
	rm -f $(OBJ) $(NAME) woody libft/libft.a libft/*o encryption/encrypt.o

re : fclean all

.PHONY : clean fclean re all
