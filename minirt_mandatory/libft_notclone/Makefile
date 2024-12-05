NAME	= 	libft.a

# printf
PRINTF	=   ft_printf/libftprintf.a

# get_next_line
GNL_DIR =	get_next_line/

GNL_SRC	=	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c

GNL_OBJ	=	$(GNL_SRC:.c=.o)

SRCS	= 	ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memset.c ft_strlen.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
			ft_tolower.c ft_toupper.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
			ft_strnstr.c ft_memcmp.c ft_strdup.c ft_atoi.c ft_calloc.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
			ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

CC 		= 	cc

FLAGS 	= 	-Wall -Wextra -Werror

OBJS	= 	$(SRCS:.c=.o)

BON_OBJ = 	$(BON_SRC:.c=.o)

all: $(NAME) $(PRINTF)

$(NAME): $(OBJS) $(GNL_OBJ)
	ar -rcs $@ $^

$(PRINTF):
	make -C ft_printf/

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

.PHONY: clean fclean all bonus re

re: fclean all

clean:
	@echo "\033[91mWhy are you using wildcards?????? \033[0m"
	rm -f *.o */*.o

fclean: clean
	rm -f $(NAME)