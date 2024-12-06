NAME = fdf_macos
CFLAGS += -Wall -Wextra -Werror -Wunreachable-code
LIBMLX = ./MLX42

HEADERS = -I./incs -I$(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit
SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: libmlx $(NAME)

libmlx: phony
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx phony
