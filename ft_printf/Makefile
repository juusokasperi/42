S := ft_printf.c ft_ltoa.c ft_xtoa.c parse_flags.c print_hex.c print_nbr.c \
	print_ptr.c print_strchar.c print_unsigned.c helper_functions.c \
	helper_functions_2.c

O := $(S:.c=.o)

H := ft_printf.h

CC := gcc

ARFLAGS = rcs

CFLAGS += -Wall -Wextra -Werror -I./

NAME := libftprintf.a

all: $(NAME)

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $O
	ar $(ARFLAGS) $@ $^

clean:
	rm -f $O

fclean: clean
	rm  -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
