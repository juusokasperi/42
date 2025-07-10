# Srcs
SRCS_DIR =	srcs/
SRCS =		main.c				init/init.c		utils/ft_atoi.c \
			init/fork.c			utils/utils.c	utils/ft_strlen.c \
			routine/philo.c		routine/philo_utils.c	routine/philo_actions.c

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
CFLAGS +=	-g -lrt
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

ifeq ($(shell uname -s)-$(shell uname -m), Darwin-arm64)
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
