# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 19:54:12 by bstrong           #+#    #+#              #
#    Updated: 2022/03/19 11:22:20 by bstrong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -O3 -g

SRC_LST		= $(notdir $(wildcard *.c))
HEADER	= 	libft.h

OBJ_PATH	=./bin/
OBJ			= $(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST)))

.PHONY	:	all clean fclean re

all: $(OBJ_PATH) $(NAME)	

$(OBJ_PATH):
	echo "Create $(OBJ_PATH)"
	mkdir -p $(OBJ_PATH)

$(NAME): ${OBJ} ${OBJ_B} $(HEADER)
	ar -rcs ${NAME} $?

$(OBJ_PATH)%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	rm -rf $(OBJ_PATH)

fclean :	clean
	rm -f $(NAME)

re		:	fclean all

