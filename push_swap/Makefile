SRCS = main.c ft_atoll.c ft_init.c ft_parse_stack.c ft_sort.c \
	ft_swap.c ft_rotate.c ft_push.c ft_reverse_rotate.c
OBJS = $(SRCS:.c=.o)

NAME = push_swap

LIBFT = libft/libft.a

HDR = push_swap.h

CC = cc
CFLAGS += -Wall -Wextra -Werror -I./libft/includes
LDFLAGS = -L./libft -lft

%.o: %.c $(HDR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT): phony
	@make -C ./libft

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@make -C ./libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C ./libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: phony fclean clean re all
