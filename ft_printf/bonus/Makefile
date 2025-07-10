S := ft_printf.c ft_ltoa.c ft_xtoa.c print_hex.c print_nbr.c \
	print_ptr.c print_str_char.c print_unsigned.c helper_functions.c \
	parse_flags.c parse_utils.c
O := $(S:.c=.o)

H := ft_printf.h

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

CC := cc
CFLAGS = -Wall -Wextra -Werror -I./

ARFLAGS = rcs

LIBFT := libft/libft.a

NAME := libftprintf.a

all: $(NAME)

$(LIBFT): phony
	@make -C ./libft

bonus: all

$O: $(LIBFT)

%.o: %.c $H
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $O
	@cp $(LIBFT) $(NAME)
	@ar $(ARFLAGS) $@ $O
	@echo "$(GREEN)✅ FT_PRINTF: Library compilation complete!$(ENDCOLOR)"

clean:
	@rm -f $O
	@make -C ./libft clean
	@echo "$(RED)✅ FT_PRINTF: Clean complete.$(ENDCOLOR)"

fclean: clean
	@rm  -f $(NAME) $(LIBFT)
	@make -C ./libft fclean
	@echo "$(RED)✅ FT_PRINTF: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all bonus phony
