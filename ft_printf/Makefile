S := ft_printf.c ft_itoa.c ft_xtoa.c parse_flags.c print_hex.c print_nbr.c \
	print_ptr.c print_strchar.c print_unsigned.c helper_functions.c

TEST_S := tests/test.c tests/int.c tests/unsigned.c tests/hex.c tests/ptr.c \
	tests/str.c tests/char.c

O := $(S:.c=.o)
TEST_O := $(TEST_S:.c=.o)

H := ft_printf.h

CC := cc

CFLAGS += -Wall -Wextra -Werror -I./

NAME := test

all: $(NAME)

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $O $(TEST_O)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $O $(TEST_O)

fclean: clean
	rm  -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
