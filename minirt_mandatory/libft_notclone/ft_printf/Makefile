NAME = ../libft.a

SRCS = 	ft_printf.c ft_print_char.c ft_print_str.c ft_print_addr.c \
		ft_parse_string.c ft_is_specifier.c ft_putstr.c \
		ft_print_nbr.c ft_itoa_ubase.c ft_putchar_n.c ft_print_hexa.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	rm -f $(OBJS)

fclean: clean

re: fclean all
