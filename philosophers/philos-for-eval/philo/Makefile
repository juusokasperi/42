# Srcs
SRCS_DIR =	srcs/
SRCS =		main.c				ft_cleanup.c								\
			init/init.c			init/init_threads.c		init/init_mutexes.c	\
			utils/ft_atoi.c		utils/utils.c								\
			routine/philo.c		routine/philo_utils.c	routine/monitor.c	\


# Objs
OBJS_DIR =	objs/
OBJS =		$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

# Name
NAME =		philo

# Header
HDR =		incs/philosophers.h
INCS =		-I./incs

# Compiler
CC = 		cc
CFLAGS +=	-Wall -Wextra -Werror -pthread $(INCS)

# Colors (for echo)
RED = 		\033[0;31m
GREEN = 	\033[0;32m
YELLOW = 	\033[1;33m
ENDCOLOR = 	\033[0m

# Rules
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ PHILO: Compilation complete!$(ENDCOLOR)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)✅ PHILO: Clean complete.$(ENDCOLOR)"

fclean:
	@rm -rf $(NAME) $(OBJS_DIR)
	@echo "$(RED)✅ PHILO: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: fclean clean re all
