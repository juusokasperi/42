SRCS := char.c eval.c hex_upper.c hex_lower.c int.c ptr.c str.c test.c unsigned.c others.c
OBJ := $(SRCS:.c=.o)

H := ft_printf.h
LIB := ../libftprintf.a

CC := cc
CFLAGS += -g -Wno-format -I./ -I../

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	ifeq ($(shell uname -p),arm)
		CFLAGS += -arch x86_64
	endif
endif

LDFLAGS = -L../ -lftprintf

NAME := test

GREEN = \033[0;32m
RED = \033[0;31m
ENDCOLOR = \033[0m

all: $(NAME)

$(LIB):
	@make -C ../

$(OBJ): $(LIB)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ FT_PRINTF: Test compilation complete.$(ENDCOLOR)"

clean:
	@make -C ../ clean
	@rm -f $(OBJ)
	@echo "$(RED)✅ FT_PRINTF: Test clean complete.$(ENDCOLOR)"

fclean:
	@make -C ../ fclean
	@rm -f $(OBJ) $(NAME)
	@echo "$(RED)✅ FT_PRINTF: Test fclean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re
