# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 12:42:26 by bstrong           #+#    #+#              #
#    Updated: 2022/03/16 20:32:04 by bstrong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minirt
CC		= clang
FLAGS	= -Wall -Wextra -Werror -g

INCLUDE	= -I ./includes -I ./libft -I ./minilibx

LIBS	= -L./libft -lft -L./minilibx -lmlx

HEADERS	= ./includes/minirt.h	./includes/keys.h 

VPATH := ./src/

SRC_PATH	=	./src/

SRC_LST		=	main.c			key_hooks.c\
				message.c	vector_operations.c\
				utils.c		colors.c		lights.c\
				list_obj.c	parser.c

OBJ_PATH		=	./bin/

OBJ				=	$(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST)))

.PHONY	:	all clean fclean re bonus

all	:	$(LIBS) $(OBJ_PATH) $(NAME)

$(LIBS)	:
		make -C ./libft all
		$ make -C ./minilibx

$(OBJ_PATH)	:
		mkdir -p $(OBJ_PATH)

$(NAME) : $(OBJ)
		$(CC) $(OBJ) $(LIBS) -framework OpenGL -framework AppKit -o $@

$(OBJ_PATH)%.o : %.c $(HEADERS)
		$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean :
	make -C ./libft clean
	make -C ./minilibx clean
	rm -rf $(OBJ_PATH)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re :fclean all