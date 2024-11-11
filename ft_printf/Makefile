S := ft_printf.c ft_ltoa.c ft_xtoa.c print_hex.c print_nbr.c \
	print_ptr.c print_strchar.c print_unsigned.c helper_functions.c \
	parse_flags.c
O := $(S:.c=.o)

H := ft_printf.h

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

CC := cc
CFLAGS = -Wall -Wextra -Werror -I./ -I./Libft

ARFLAGS = rcs

LIBFT := Libft/libft.a
LIBFT_H := Libft/libft.h

NAME := libftprintf.a

all: $(NAME)

$(LIBFT) $(LIBFT_H):
	@make -C ./Libft
	@make -C ./Libft clean

bonus: all

$O: $(LIBFT) $(LIBFT_H)

%.o: %.c $H
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $O
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
