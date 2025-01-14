# Sources:
SRCS_DIR = srcs/
C_SRCS = client.c
S_SRCS = server.c

# Objects:
OBJS_DIR = objs/
C_OBJS = $(addprefix $(OBJS_DIR), $(C_SRCS:.c=.o))
S_OBJS = $(addprefix $(OBJS_DIR), $(S_SRCS:.c=.o))

# Header:
H = incs/minitalk.h
INCS = -I./libft/includes -I./incs/

# Compiler:
CC = cc
CFLAGS += -Wall -Wextra -Werror $(INCS)
LDFLAGS = -L./libft -lft

# Colors:
GREEN = \033[0;32m
RED = \033[0;31m
ENDCOLOR = \033[0m

NAME = minitalk
LIBFT = libft/libft.a

# Rules:
all: $(NAME)

$(NAME): server client

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(H)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): phony
	@make -C ./libft

client: $(LIBFT) $(C_OBJS)
	@$(CC) $(CFLAGS) $(C_OBJS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ MINITALK: Client compilation complete!$(ENDCOLOR)"

server: $(LIBFT) $(S_OBJS)
	@$(CC) $(CFLAGS) $(S_OBJS) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ MINITALK: Server compilation complete!$(ENDCOLOR)"

bonus: server_bonus client_bonus

client_bonus: client

server_bonus: server

clean:
	@make -C ./libft clean
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)✅ MINITALK: Clean complete.$(ENDCOLOR)"

fclean:
	@make -C ./libft fclean
	@rm -rf $(OBJS_DIR) client server
	@echo "$(RED)✅ MINITALK: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all bonus server_bonus client_bonus phony
