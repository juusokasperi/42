NAME = fdf_macos
CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -g
LIBMLX = ./MLX42

HEADERS = incs/fdf.h incs/terminal_colors.h

HEADERS_PATH = -I./incs -I$(LIBMLX)/include -I./libft/includes
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit -L./libft -lft

SRCS = main.c \
	\
	read_map/read_map.c read_map/read_map_utils.c read_map/read_map_utils_2.c \
	\
	draw/draw.c draw/draw_utils.c draw/draw_utils_2.c \
	\
	controls/controls.c \
	\
	init/init.c init/calculate.c \
	\
	exit.c
SRC_DIR = srcs/

OBJ_DIR = objs/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LIBFT = libft/libft.a

all: libmlx $(NAME)

$(LIBFT): phony
	@make -C libft

libmlx: phony
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(sort $(dir $(OBJS)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS_PATH) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libmlx phony
