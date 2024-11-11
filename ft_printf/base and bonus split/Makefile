S := ft_printf.c ft_ltoa.c ft_xtoa.c print_hex.c print_nbr.c \
	print_ptr.c print_strchar.c print_unsigned.c helper_functions.c \
	helper_functions_2.c
S_PATH := $(addprefix ./base/, $S)

O := $(S_PATH:.c=.o)
H := ./base/ft_printf.h

S_BONUS := ft_printf_bonus.c ft_ltoa_bonus.c ft_xtoa_bonus.c \
	print_hex_bonus.c print_nbr_bonus.c print_ptr_bonus.c \
	print_strchar_bonus.c print_unsigned_bonus.c helper_functions_bonus.c \
	helper_functions_2_bonus.c parse_flags_bonus.c
S_PATH := $(addprefix ./bonus/, $(S_BONUS))

O_BONUS := $(S_PATH:.c=.o)
H_BONUS := ./bonus/ft_printf_bonus.h


GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

CC := gcc
CFLAGS += -Wall -Wextra -Werror -I./

ARFLAGS = rcs

LIBFT := libft.a
LIBFT_H := libft.h

NAME := libftprintf.a

all: $(NAME)

$(LIBFT) $(H):
	@make -C ./Libft
	@cp ./Libft/$(LIBFT) ./
	@cp ./Libft/$(LIBFT_H) ./
	@make -C ./Libft fclean

bonus: .bonus

.bonus: $(LIBFT) $(O_BONUS)
	@rm -f $(NAME)
	ar $(ARFLAGS) $(NAME) $(O_BONUS)
	@cp $(H_BONUS) ./
	@echo "$(GREEN)✅ FT_PRINTF: Bonus compilation complete!$(ENDCOLOR)"
	@touch .bonus

$(O): %.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(O_BONUS): %_bonus.o: %_bonus.c $(H_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $O
	@rm -f $(NAME)
	ar $(ARFLAGS) $@ $O
	@cp $(H) ./
	@echo "$(GREEN)✅ FT_PRINTF: Library compilation complete!$(ENDCOLOR)"

clean:
	rm -f $O $(O_BONUS)
	@echo "$(RED)✅ FT_PRINTF: Clean complete.$(ENDCOLOR)"

fclean: clean
	rm  -f $(NAME) $(BONUS_NAME) $(LIBFT) $(LIBFT_H) ft_printf.h ft_printf_bonus.h
	@echo "$(RED)✅ FT_PRINTF: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all bonus
