# Srcs
SRCS_DIR =	srcs/
SRCS =		main.c				init/init.c				init/init_threads.c	\
			init/init_mutexes.c	utils/ft_atoi.c			utils/get_time_ms.c	\
			utils/ft_usleep.c	utils/ft_free.c			exit/ft_cleanup.c	\
			routine/philo.c		routine/philo_utils.c	routine/monitor.c

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
CFLAGS +=	-Wall -Werror -Wextra -pthread $(INCS)

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

ifeq ($(shell uname -s)-$(shell uname -m), Darwin-arm64)
# Docker stuff
CONTAINER_NAME =	valgrind-env
valgrind: fclean
	@docker start $(CONTAINER_NAME) || (docker run -dit \
	--name $(CONTAINER_NAME) ubuntu /bin/bash \
	&& docker exec $(CONTAINER_NAME) apt-get update \
	&& docker exec $(CONTAINER_NAME) apt-get install -y make gcc valgrind)
	@docker exec $(CONTAINER_NAME) rm -rf /app/
	@docker exec $(CONTAINER_NAME) mkdir -p /app/
	@docker cp . $(CONTAINER_NAME):/app/
	@docker exec $(CONTAINER_NAME) make -C /app/ debug --no-print-directory
	@echo "$(GREEN)✅ PHILO: Valgrind docker compilation complete!$(ENDCOLOR)"
valgrind_clean:
	@docker start $(CONTAINER_NAME)
	@docker exec $(CONTAINER_NAME) rm -rf /app/
	@echo "$(RED)✅ PHILO: Valgrind FClean complete.$(ENDCOLOR)"
endif

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
