SRC := main.c test_isalpha.c test_isdigit.c test_isalnum.c test_isascii.c \
	test_isprint.c test_strlen.c test_memset.c test_bzero.c test_memcpy.c \
	test_memmove.c test_strlcpy.c test_strlcat.c test_toupper.c \
	test_tolower.c test_strchr.c test_strrchr.c test_strncmp.c test_memchr.c \
	test_memcmp.c test_strnstr.c test_atoi.c test_calloc.c test_strdup.c \
	test_substr.c test_strjoin.c test_strtrim.c test_split.c test_itoa.c \
	test_strmapi.c test_striteri.c test_lstnew.c test_lstaddfront.c \
	test_lstsize.c test_lstlast.c test_lstaddback.c test_lstdelone.c \
	test_lstclear.c test_lstiter.c test_lstmap.c

O := $(SRC:.c=.o)

H := libft.h
LIB := libft.a

CC = gcc
CFLAGS += -Wall -Wextra -Werror -I./
LDFLAGS = -L./ -lft

NAME := test

GREEN := \033[0;32m
RED := \033[0;31m
ENDCOLOR := \033[0m

all: $(NAME)

$(LIB) $H:
	@make -C ../
	@make -C ../ bonus
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
	@echo "$(GREEN)✅ LIBFT: Test clean complete.$(ENDCOLOR)"

fclean:
	rm -f $O $H $(LIB) $(NAME)
	@echo "$(GREEN)✅ LIBFT: Test fclean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re
