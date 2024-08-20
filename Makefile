NAME = minirt

CC = cc

CFLAGS = -Wall -Wextra -Werror

#CFLAGS += -fsanitize=address -g3

SRCS = minirt.c camera.c vectors.c hooks.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

ifeq ($(shell uname), Linux)
MLXOS = minilibx-linux
MLXFLAGS = -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm
MLXOBJ =  -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux -O3 -c

else
MLXOS = mlx
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLXOBJ = -Wall -Wextra -Werror -Imlx -c
endif

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLXOS)
	make -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(LIBFT) -I. $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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