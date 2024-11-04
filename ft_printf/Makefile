S := ft_printf.c ft_ltoa.c ft_xtoa.c parse_flags.c print_hex.c print_nbr.c \
	print_ptr.c print_strchar.c print_unsigned.c helper_functions.c \
	helper_functions_2.c
O := $(S:.c=.o)
H := ft_printf.h

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

CC := gcc
CFLAGS += -Wall -Wextra -Werror -I./

ARFLAGS = rcs

NAME := libftprintf.a

all: $(NAME)

bonus: all

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $O
	ar $(ARFLAGS) $@ $^
	@echo "$(GREEN)✅ FT_PRINTF: Library compilation complete!$(ENDCOLOR)"

clean:
	rm -f $O
	@echo "$(RED)✅ FT_PRINTF: Clean complete.$(ENDCOLOR)"

fclean: clean
	rm  -f $(NAME)
	@echo "$(RED)✅ FT_PRINTF: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all
