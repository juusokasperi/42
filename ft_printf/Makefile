S := ft_printf.c ft_ltoa.c ft_xtoa.c print_hex.c print_nbr.c \
	print_ptr.c print_str.c print_unsigned.c print_char.c
O := $(S:.c=.o)

H := ft_printf.h

GREEN = \033[0;32m
RED = \033[0;31m
ENDCOLOR = \033[0m

CC := cc
CFLAGS = -Wall -Wextra -Werror -I./

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	ifeq ($(shell uname -p),arm)
		CFLAGS += -arch x86_64
	endif
endif

ARFLAGS = rcs

LIBFT := libft/libft.a

NAME := libftprintf.a

all: $(NAME)

$(LIBFT): phony
	@make -C ./libft

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $O
	@cp $(LIBFT) $(NAME)
	@ar $(ARFLAGS) $@ $O
	@echo "$(GREEN)✅ FT_PRINTF: Library compilation complete!$(ENDCOLOR)"

clean:
	@make -C ./libft clean
	@rm -f $O $(O_BONUS)
	@echo "$(RED)✅ FT_PRINTF: Clean complete.$(ENDCOLOR)"

fclean:
	@make -C ./libft fclean
	@rm  -f $O $(O_BONUS) $(NAME)
	@echo "$(RED)✅ FT_PRINTF: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all phony
