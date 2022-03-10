NAME = a
CC = gcc
FLAGS = -Wall -Wextra -Werror -g


SRC	=	parser.c list_obj.c

OBJ	= $(patsubst %.c,%.o,$(SRC))

LIBS	= -L./libft -lft

.PHONY : all clean fclean re bonus

all: $(LIBS) $(NAME)

#bonus: all

$(LIBS):
	make -C ./libft all

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

%.o : %.c
	$(CC) $(FLAGS) -I ./libft -I ./inc -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all