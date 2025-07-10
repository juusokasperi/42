#	Sources
SRCS_DIR =	srcs/
SRCS =		main.c																\
			init/ft_init.c	init/ft_init_join.c			init/ft_parse_stack.c	\
			moves/ft_push.c	moves/ft_reverse_rotate.c	moves/ft_rotate.c		\
			moves/ft_swap.c														\
			sort/ft_calculate_execute.c					sort/ft_move.c			\
			sort/ft_sort_utils.c						sort/ft_sort.c			\
			sort/ft_target.c													\
			utils/ft_atoll.c							utils/ft_stack_utils.c

SRCS_BONUS =	checker/ft_checker_init_bonus.c				\
				checker/ft_checker_init_join_bonus.c		\
				checker/ft_checker_parse_bonus.c			\
				checker/ft_checker_bonus.c					\
				checker/ft_checker_push_bonus.c				\
				checker/ft_checker_reverse_rotate_bonus.c	\
				checker/ft_checker_rotate_bonus.c 			\
				checker/ft_checker_swap_bonus.c				\
				checker/ft_checker_free_bonus.c				\
				checker/ft_atoll_bonus.c

#	Objects
OBJS = 			$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_DIR = 		objs/
OBJS_BONUS = 	$(addprefix $(OBJS_DIR), $(SRCS_BONUS:.c=.o))

NAME =			push_swap
BONUS_NAME =	checker
LIBFT =			libft/libft.a

#	Header
HDR =			includes/push_swap.h
HDR_BONUS =		includes/checker_bonus.h

#	Compiler
CC =		cc
INCS =		-I./libft/includes -I./includes
CFLAGS +=	-Wall -Wextra -Werror $(INCS)
LDFLAGS =	-L./libft -lft

#	Colors
RED =		\033[0;31m
GREEN =		\033[0;32m
YELLOW =	\033[1;33m
ENDCOLOR =	\033[0m

#	Rules
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)checker/%.o: $(SRCS_DIR)checker/%.c $(HDR_BONUS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT): phony
	@make -C ./libft

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
