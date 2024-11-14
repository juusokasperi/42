S := ft_printf.c ft_ltoa.c ft_xtoa.c print_hex.c print_nbr.c \
	print_ptr.c print_str.c print_unsigned.c print_char.c
O := $(S:.c=.o)

H := ft_printf.h

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

CC := cc
CFLAGS = -Wall -Wextra -Werror -I./

ARFLAGS = rcs

LIBFT := Libft/libft.a

NAME := libftprintf.a

all: $(NAME)

$(LIBFT):
	@make -C ./Libft
	@make -C ./Libft clean

$O: $(LIBFT) $(LIBFT_H)

%.o: %.c $H
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $O
	@cp $(LIBFT) $(NAME)
	@ar $(ARFLAGS) $@ $O
	@echo "$(GREEN)✅ FT_PRINTF: Library compilation complete!$(ENDCOLOR)"

clean:
	@rm -f $O $(O_BONUS)
	@echo "$(RED)✅ FT_PRINTF: Clean complete.$(ENDCOLOR)"

fclean: clean
	@rm  -f $(NAME) $(LIBFT)
	@echo "$(RED)✅ FT_PRINTF: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all bonus
