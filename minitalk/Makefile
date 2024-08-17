C_SRCS := client.c
S_SRCS := server.c

C_OBJS := $(C_SRCS:.c=.o)
S_OBJS := $(S_SRCS:.c=.o)

H := minitalk.h ft_printf.h libft.h

CC := gcc
CFLAGS += -Wall -Wextra -Werror -I./
LDFLAGS := -L./ -lft -lftprintf

NAME := minitalk

all: client server

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

client: $(C_OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

server: $(S_OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(C_OBJS) $(S_OBJS)

fclean: clean
	rm  -f client server

re: fclean all

.PHONY: clean fclean re all




