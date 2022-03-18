NAME	= minirt
CC		= gcc
FLAGS	= -Wall -Wextra -Wextra -O3 -g
LIBS	= -L./libft -lft
INC		= -I ./includes -I ./libft

VPATH	= ./src
PROGRESS = progress

ifndef U_OS
	U_OS = $(shell uname -s)
	ifeq ($(U_OS), Darwin)
		LIBS	+=	-L./minilibx -lmlx
		INC		+= -I ./minilibx
	endif
	ifeq ($(U_OS), Linux)
		LIBS	+= -L./minilibx_linux -lmlx
		INC		+= -I ./minilibx_linux
	endif
endif

ifdef ECHO
	HIT_TOTAL = $(words $(SRC_LST) minirt)
	HIT_COUNT = $(eval HIT_N != expr $(HIT_N) + 1) $(HIT_N)
	ECHO =	echo c $(HIT_COUNT) t$(HIT_TOTAL) $@
endif


SRC_LST		= $(notdir $(wildcard ./src/*.c))
HEADERS		= $(wildcard ./inc/*.h)

OBJ_PATH	=./bin/
OBJ			= $(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST)))

.PHONY:		all clean fclean re check
.SILENT:	$(OBJ) $(OBJ_PATH) $(NAME) all clean fclean re check

all: $(OBJ_PATH) $(NAME)

$(LIBS):
		make -C ./libft all
		make -C ./minilibx

$(PROGRESS):
	g++ main_pr.cpp -o $@

$(OBJ_PATH):
	echo $(INC)
	echo "Create $(OBJ_PATH)"
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ_PATH) $(OBJ)
	$(ECHO)
	$(CC) $(OBJ) $(LIBS) -framework OpenGL -framework AppKit -o $@

$(OBJ_PATH)%.o : %.c $(HEADERS) $(LIBS)
	$(ECHO)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean :
	echo "Delete ./bin/"
	make -C ./libft clean
	make -C ./minilibx clean
	rm -rf $(OBJ_PATH)

fclean : clean
	echo "Delete $(NAME)"
	make -C ./libft fclean
	rm -f $(NAME) $(PROGRESS)

re : fclean all