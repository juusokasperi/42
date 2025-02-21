# Srcs
SRCS_DIR =	srcs/
SRCS =		main.c 				utils/ft_error.c		utils/ft_strlen.c	\
			utils/ft_atoi.c		utils/get_time_ms.c		utils/ft_usleep.c	\
			utils/print_msg.c	init/init.c				init/init_threads.c	\
			utils/philo_unlock_forks.c					utils/ft_free.c		\
			utils/ft_strcmp.c	utils/min_max_mid.c							\
			exit/ft_cleanup.c	routine/philo.c			routine/monitor.c	\
			routine/monitor_priority.c

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
ifeq ($(MAKECMDGOALS), debug)
	CFLAGS +=	-g
endif
CFLAGS +=	-Wall -Wextra -pthread $(INCS)

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

# Docker stuff
CONTAINER_NAME =	valgrind-env
valgrind: fclean
	docker start $(CONTAINER_NAME) || (docker run -dit \
	--name $(CONTAINER_NAME) ubuntu /bin/bash \
	&& docker exec $(CONTAINER_NAME) apt-get update \
	&& docker exec $(CONTAINER_NAME) apt-get install -y make gcc valgrind)
	docker exec $(CONTAINER_NAME) rm -rf /app/
	docker exec $(CONTAINER_NAME) mkdir -p /app/
	docker cp . $(CONTAINER_NAME):/app/
	docker exec $(CONTAINER_NAME) make -C /app/ debug

debug: re

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ PHILO: Compilation complete!$(ENDCOLOR)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)✅ PHILO: Clean complete.$(ENDCOLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✅ PHILO: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: fclean clean re all debug valgrind
