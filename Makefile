NAME	= minirt
CC		= gcc
FLAGS	= -Wall -Wextra -Wextra -O0 -g
LIBS	= -L ./libft -lft
INC		= -I ./includes -I ./libft

VPATH	= ./src ./src_bonus
PROGRESS = progress

ifndef U_OS
	U_OS = $(shell uname -s)
	ifeq ($(U_OS), Darwin)
		LIBS	+=	-L./minilibx -lmlx 
		SPEC	= -framework OpenGL -framework AppKit
		INC		+= -I ./minilibx
	endif
	ifeq ($(U_OS), Linux)
		LIBS	+= -L./minilibx_linux -lmlx
		SPEC	=  -lXext -lX11 -lm -lz
		INC		+= -I ./minilibx_linux
	endif
endif

ifdef ECHO
	HIT_TOTAL = $(words $(SRC_LST) minirt)
	HIT_COUNT = $(eval HIT_N != expr $(HIT_N) '+' 1) $(HIT_N)
	ECHO =	echo c $(HIT_COUNT) t$(HIT_TOTAL) $@
endif


SRC_LST		=	colors.c				compute_light.c		cylinder.c\
				image.c					key_hooks.c			lights.c\
				list_obj.c				main.c				message.c\
				parser.c				plane.c				sphere.c\
				trasing.c				utils.c				vector_operations.c\
				vector_operations2.c
SRC_LST_B	=	checkerboard_bonus.c	colors_bonus.c		compute_light_bonus.c\
				cone_bonus.c			cylinder_bonus.c	get_norm_bonus.c\
				image_bonus.c			key_hooks_bonus.c	lights_bonus.c\
				list_obj_bonus.c		main_bonus.c		message_bonus.c\
				parser_bonus.c			plane_bonus.c		ray_trase_bonus.c\
				sphere_bonus.c			trasing_bonus.c		utils_bonus.c\
				vector_operations_bonus.c		vector_operations2_bonus.c
HEADERS		= ./includes/errors.h	./includes/keys.h	./includes/minirt_bonus.h	./includes/minirt.h

OBJ_PATH	=./bin/
OBJ			= $(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST)))
OBJ_B		= $(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST_B)))

.PHONY:		 all bonus clean fclean re bonus
#.SILENT:	all clean fclean re

all:  $(LIBS) $(OBJ_PATH) $(NAME)

$(LIBS):
		make -C ./libft all
		make -C ./minilibx

$(PROGRESS):
	g++ main_pr.cpp -o $@

$(OBJ_PATH):
	echo "Create $(OBJ_PATH)"
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ_PATH) $(OBJ)
	$(ECHO)
	$(CC) $(OBJ) $(LIBS) $(SPEC) -o $@


$(OBJ_PATH)%.o : %.c $(HEADERS)
	$(ECHO)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

bonus: $(LIBS) $(OBJ_PATH) $(OBJ_B)
	$(ECHO)
	$(CC) $(OBJ_B) $(LIBS) $(SPEC) -o $(NAME)

$(OBJ_PATH)%_bonus.o : %_bonus.c $(HEADERS)
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