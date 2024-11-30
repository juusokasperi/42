SRCS_DIR = srcs/
SRCS = main.c ft_atoll.c ft_init.c ft_parse_stack.c ft_sort.c \
	ft_swap.c ft_rotate.c ft_push.c ft_reverse_rotate.c \
	ft_stack_utils.c ft_target.c ft_calculate_execute.c \
	ft_move.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_DIR = objs/

NAME = push_swap

LIBFT = libft/libft.a

HDR = includes/push_swap.h
INCS = -I./libft/includes -I./includes

CC = cc
CFLAGS += -Wall -Wextra -Werror -g $(INCS)
LDFLAGS = -L./libft -lft

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HDR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT): phony
	@make -C ./libft

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@make -C ./libft clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make -C ./libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: phony fclean clean re all
