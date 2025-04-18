NAME = minirt

CC = cc

INCLUDES = ./includes

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES) -pthread -Ofast -flto

SRCSPATH	=	srcs
MATRIX 		=	$(SRCSPATH)/matrix
PARSING		=	$(SRCSPATH)/parsing
RENDER		=	$(SRCSPATH)/render
SHAPES		=	$(SRCSPATH)/shapes
TUPLES		=	$(SRCSPATH)/tuples
UTILS		=	$(SRCSPATH)/utils

SRCS		=	$(SRCSPATH)/minirt.c \
				$(MATRIX)/matrix_cmp.c \
				$(MATRIX)/matrix_ops.c \
				$(MATRIX)/matrix_ops2.c \
				$(MATRIX)/matrix_ops3.c \
				$(MATRIX)/matrix_ops4.c \
				$(MATRIX)/matrix_ops5.c \
				$(MATRIX)/matrix_utils.c \
				\
				\
				\
				$(PARSING)/parse_shapes.c \
				$(PARSING)/parse_elements.c \
				$(PARSING)/parsing.c \
				$(PARSING)/parse_bonus.c \
				$(PARSING)/parsing_utils.c \
				$(PARSING)/parsing_utils2.c \
				$(PARSING)/parsing_utils3.c \
				$(PARSING)/read_file.c \
				\
				\
				\
				$(RENDER)/camera.c \
				$(RENDER)/color.c \
				$(RENDER)/color_utils.c \
				$(RENDER)/hooks.c \
				$(RENDER)/hooks2.c \
				$(RENDER)/hooks3.c \
				$(RENDER)/intersects.c \
				$(RENDER)/intersects2.c \
				$(RENDER)/light.c \
				$(RENDER)/render.c \
				$(RENDER)/threads.c \
				\
				\
				\
				$(SHAPES)/cone.c \
				$(SHAPES)/cone_hit.c \
				$(SHAPES)/cylinder.c \
				$(SHAPES)/cylinder_hit.c \
				$(SHAPES)/material.c \
				$(SHAPES)/normal.c \
				$(SHAPES)/pattern.c \
				$(SHAPES)/plane.c \
				$(SHAPES)/shapes.c \
				$(SHAPES)/sphere.c \
				$(SHAPES)/transformations.c \
				$(SHAPES)/transformations2.c \
				$(SHAPES)/textures.c \
				\
				\
				\
				$(TUPLES)/tuple_utils.c \
				$(TUPLES)/tuple_utils2.c \
				$(TUPLES)/vector_math.c \
				$(TUPLES)/vector_math2.c \
				$(TUPLES)/vector_ops.c \
				$(TUPLES)/vector_utils.c \
				\
				\
				\
				$(UTILS)/frees.c \
				$(UTILS)/init.c \
				$(UTILS)/utils.c \
				$(UTILS)/err.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

ifeq ($(shell uname), Linux)
MLXOS = minilibx-linux
MLXFLAGS = -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lbsd
MLXOBJ =  -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux -O3 -c

else
MLXOS = mlx
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLXOBJ = -Wall -Wextra -Werror -Imlx -c
endif

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLXOS) -j2
	make -C $(LIBFT_DIR) -j2
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I. $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -g3 -c $< -o $@

run: re
	./$(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re