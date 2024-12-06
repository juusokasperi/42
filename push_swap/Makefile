SRCS_DIR = srcs/

SRCS = main.c ft_atoll.c ft_init.c ft_parse_stack.c ft_sort.c \
	ft_swap.c ft_rotate.c ft_push.c ft_reverse_rotate.c \
	ft_stack_utils.c ft_target.c ft_calculate_execute.c \
	ft_move.c ft_sort_utils.c ft_init_join.c

SRCS_BONUS = checker/ft_checker_init_bonus.c checker/ft_checker_init_join_bonus.c  \
	checker/ft_checker_parse_bonus.c checker/ft_checker_bonus.c \
	checker/ft_checker_push_bonus.c checker/ft_checker_reverse_rotate_bonus.c \
	checker/ft_checker_rotate_bonus.c checker/ft_checker_swap_bonus.c ft_atoll.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_DIR = objs/
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(SRCS_BONUS:.c=.o))

NAME = push_swap
BONUS_NAME = checker

LIBFT = libft/libft.a

HDR = includes/push_swap.h
HDR_BONUS = includes/checker.h
INCS = -I./libft/includes -I./includes

CC = cc
CFLAGS += -Wall -Wextra -Werror -g $(INCS)
LDFLAGS = -L./libft -lft

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
ENDCOLOR = \033[0m

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)checker/%.o: $(SRCS_DIR)checker/%.c $(HDR_BONUS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT): phony
	make -C ./libft

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ PUSH_SWAP: Compilation complete!$(ENDCOLOR)"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LDFLAGS) -o $(BONUS_NAME)
	@echo "$(YELLOW)✅ PUSH_SWAP: Checker compilation complete!$(ENDCOLOR)"

clean:
	@make -C ./libft clean
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)✅ PUSH_SWAP: Clean complete.$(ENDCOLOR)"

fclean: clean
	@make -C ./libft fclean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(RED)✅ PUSH_SWAP: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: phony fclean clean re all bonus
