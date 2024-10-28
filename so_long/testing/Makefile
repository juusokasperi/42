NAME := test
INCLUDES := -I/opt/X11/include -Imlx
LIBMLX := ./mlx

H := -I./ -I./$(LIMBLX)
MLX_FLAGS := -Lmlx -lmlx -L/usr/x11/lib -lXext -lX11 -framework OpenGL -framework AppKit

CC := gcc
CFLAGS := -Wall -Wextra -Werror

S := main.c
O := $(S:.c=.o)

all: libmlx $(NAME)

libmlx:
	@make -C mlx

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $O
	$(CC) $(CFLAGS) $O $(MLX_FLAGS) -o $(NAME)

clean:
	@rm -rf $O

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
