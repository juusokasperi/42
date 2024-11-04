SRCS := char.c eval.c hex.c int.c ptr.c str.c test.c unsigned.c
OBJ := $(SRCS:.c=.o)

H := ft_printf.h
LIB := libftprintf.a

CC := gcc
CFLAGS += -Wall -Wextra -Werror -I./

LDFLAGS = -L./ -lftprintf

NAME := test

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

all: $(NAME)

$(LIB) $H:
	@make -C ../
	@cp ../$(LIB) ./
	@cp ../$H ./
	@make -C ../ fclean

$(OBJ): $(LIB) $H

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ FT_PRINTF: Test compilation complete.$(ENDCOLOR)"

clean:
	rm -f $(OBJ)
	@echo "$(RED)✅ FT_PRINTF: Test clean complete.$(ENDCOLOR)"

fclean:
	rm -f $(OBJ) $(NAME) $(LIB) $(H)
	@echo "$(RED)✅ FT_PRINTF: Test fclean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re
