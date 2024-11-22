C_SRCS := client.c
S_SRCS := server.c
C_OBJS := $(C_SRCS:.c=.o)
S_OBJS := $(S_SRCS:.c=.o)

BONUS_C_SRCS := client_bonus.c
BONUS_S_SRCS := server_bonus.c
BONUS_C_OBJS := $(BONUS_C_SRCS:.c=.o)
BONUS_S_OBJS := $(BONUS_S_SRCS:.c=.o)

H := minitalk.h

CC := gcc
CFLAGS += -Wall -Wextra -Werror -I./ -I./libft/includes
LDFLAGS := -L./libft -lft

LIB := libft/libft.a

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

NAME := minitalk

all: $(NAME)

$(NAME): server client

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): phony
	@make -C ./libft

client: $(LIB) $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ MINITALK: Client compilation complete!$(ENDCOLOR)"

server: $(LIB) $(S_OBJS)
	$(CC) $(CFLAGS) $(S_OBJS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ MINITALK: Server compilation complete!$(ENDCOLOR)"

clean:
	@make -C ./libft clean
	rm -f $(C_OBJS) $(S_OBJS) $(BONUS_C_OBJS) $(BONUS_S_OBJS)
	@echo "$(RED)✅ MINITALK: Clean complete.$(ENDCOLOR)"

fclean:
	@make -C ./libft fclean
	rm  -f $(C_OBJS) $(S_OBJS) $(BONUS_C_OBJS) $(BONUS_S_OBJS) \
	client server client_bonus server_bonus
	@echo "$(RED)✅ MINITALK: FClean complete.$(ENDCOLOR)"

bonus: server_bonus client_bonus

client_bonus: $(LIB) $(BONUS_C_OBJS)
	$(CC) $(CFLAGS) $(BONUS_C_OBJS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ MINITALK: Bonus client compilation complete!$(ENDCOLOR)"

server_bonus: $(LIB) $(BONUS_S_OBJS)
	$(CC) $(CFLAGS) $(BONUS_S_OBJS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ MINITALK: Bonus server compilation complete!$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all client server bonus server_bonus client_bonus phony
