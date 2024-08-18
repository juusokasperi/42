C_SRCS := client.c
S_SRCS := server.c

C_OBJS := $(C_SRCS:.c=.o)
S_OBJS := $(S_SRCS:.c=.o)

H := minitalk.h

CC := gcc
CFLAGS += -Wall -Wextra -Werror -I./ -I./libft -I./ft_printf
LDFLAGS := -L./libft -lft -L./ft_printf -lftprintf

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

NAME := minitalk

all: $(NAME)

$(NAME): server client

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

libs:
	@make -C libft
	@make -C ft_printf

client: libs $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ MINITALK: Client compilation complete!$(ENDCOLOR)"

server: libs $(S_OBJS)
	$(CC) $(CFLAGS) $(S_OBJS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ MINITALK: Server compilation complete!$(ENDCOLOR)"

clean:
	@make -C libft clean
	@make -C ft_printf clean
	rm -f $(C_OBJS) $(S_OBJS)
	@echo "$(RED)✅ MINITALK: Clean complete.$(ENDCOLOR)"

fclean: clean
	@make -C libft fclean
	@make -C ft_printf fclean
	rm  -f client server
	@echo "$(RED)✅ MINITALK: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all




