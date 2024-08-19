SRC := main.c
O := $(SRC:.c=.o)

H := libft.h
LIB := libft.a

CC = gcc
CFLAGS += -Wall -Wextra -Werror -I./
LDFLAGS = -L./ -lft

NAME := test

GREEN := \033[0;92m
RED := \033[0;91m
ENDCOLOR := \033[0m

all: $(NAME)

$(LIB) $H:
	@make -C ../
	@cp ../$(LIB) ./
	@cp ../$H ./
	@make -C ../ fclean

$O: $(LIB) $H

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $O
	$(CC) $(CFLAGS) $O $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ LIBFT: Test compilation complete!$(ENDCOLOR)"

clean:
	rm -f $O
	@echo "$(GREEN)✅ LIBFT: Clean complete.$(ENDCOLOR)"

fclean:
	rm -f $O $H $(LIB) $(NAME)
	@echo "$(GREEN)✅ LIBFT: Fclean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re
