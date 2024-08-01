S := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

O := $(S:.c=.o)

H := libft.h

CC := cc

CFLAGS += -Wall -Wextra -Werror -I./

ARFLAGS := -rcs

NAME := libft.a

all: $(NAME)

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $O
	ar $(ARFLAGS) $(NAME) $O

clean:
	rm -f $O

fclean: clean
	rm  -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
