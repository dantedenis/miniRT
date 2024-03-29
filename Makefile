NAME	= minirt
CC		= clang
FLAGS	= -Wall -Wextra -Wextra -O3 -g
LIBS	= -L ./libft -lft
INC		= -I ./includes -I ./libft
MLX		= ./minilibx

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
		MLX		= ./minilibx_linux
	endif
endif

SRC_LST		=	colors.c				compute_light.c		cylinder.c\
				image.c					key_hooks.c			lights.c\
				list_obj1.c				list_obj2.c			message.c\
				parser.c				plane.c				sphere.c\
				trasing.c				utils.c				vector_operations.c\
				vector_operations2.c	main.c
SRC_LST_B	=	checkerboard_bonus.c	colors_bonus.c		compute_light_bonus.c\
				cone_bonus.c			cylinder_bonus.c	get_norm_bonus.c\
				image_bonus.c			key_hooks_bonus.c	lights_bonus.c\
				main_bonus.c			message_bonus.c		rotate_bonus.c\
				parser_bonus.c			plane_bonus.c		ray_trase_bonus.c\
				sphere_bonus.c			trasing_bonus.c		utils_bonus.c\
				vector_operations_bonus.c		vector_operations2_bonus.c\
				list_obj1_bonus.c	list_obj2_bonus.c

HEADERS		= ./includes/errors.h	./includes/keys.h	./includes/minirt_bonus.h	./includes/minirt.h

OBJ_PATH	=./bin/
OBJ			= $(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST)))
OBJ_B		= $(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LST_B)))

.PHONY:		 all bonus clean fclean re bonus

all:  $(LIBS) $(OBJ_PATH) $(NAME)

$(LIBS):
		make -C ./libft all
		make -C ${MLX}

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
	make -C ${MLX} clean
	rm -rf $(OBJ_PATH)

fclean : clean
	echo "Delete $(NAME)"
	make -C ./libft fclean
	rm -f $(NAME) $(PROGRESS)

re : fclean all