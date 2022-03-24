# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 19:54:12 by bstrong           #+#    #+#              #
#    Updated: 2022/03/21 21:16:25 by bstrong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -O3 -g

SRC_LST		=	ft_atof.c				ft_atoi.c			ft_calloc.c\
				ft_isalnum.c			ft_isalpha.c		ft_isascii.c\
				ft_isdigit.c			ft_isprint.c		ft_isupper.c\
				ft_itoa.c				ft_bzero.c			ft_substr.c\
				ft_lstiter_bonus.c		ft_lstlast_bonus.c	ft_striteri.c\
				ft_lstmap_bonus.c		ft_lstnew_bonus.c	ft_strjoin.c\
				ft_lstsize_bonus.c		ft_memchr.c			ft_memcmp.c\
				ft_memcpy.c				ft_memmove.c		ft_memset.c\
				ft_putchar_fd.c			ft_putendl_fd.c		ft_putnbr_fd.c\
				ft_putstr_fd.c			ft_split.c			ft_strchr.c\
				ft_lstadd_back_bonus.c	ft_strdup.c			ft_strlcat.c\
				ft_lstclear_bonus.c		ft_strlcpy.c		ft_strlen.c\
				ft_lstdelone_bonus.c	ft_strmapi.c		ft_strncmp.c\
				ft_strnstr.c			ft_strrchr.c		ft_strtrim.c\
				ft_lstadd_front_bonus.c	ft_tolower.c		ft_toupper.c\
				get_next_line.c

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

