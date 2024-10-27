SRCS = ft_putchar.c ft_putstr.c ft_strcmp.c ft_strlen.c ft_swap.c
PATH_SRCS = $(addprefix ./srcs/, $(SRCS))

OBJS = $(PATH_SRCS:.c=.o)

HDR = libft.h
PATH_HDR = $(addprefix $(INCLUDES), $(HDR))
INCLUDES = ./includes/

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

CC = gcc
CFLAGS += -Wall -Wextra -Werror -I$(INCLUDES)

ARFLAGS = -rcs

NAME = libft.a

all: $(NAME)

%.o: %.c $(PATH_HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar $(ARFLAGS) $(NAME) $(OBJS)
	@echo "$(GREEN)✅ LIBFT: Library compilation complete!$(ENDCOLOR)"

clean:
	rm -f $(OBJS)
	@echo "$(RED)✅ LIBFT: Library clean done.$(ENDCOLOR)"


fclean:
	rm -f $(OBJS) $(NAME)
	@echo "$(RED)✅ LIBFT: Library fclean done.$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re
