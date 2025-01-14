#	Sources
SRCS =	main.c 					utils.c													\
		read_map/read_map.c		read_map/read_map_utils.c	read_map/colors_utils.c		\
		draw/draw.c				draw/transformations.c		draw/draw_utils.c			\
		draw/colors.c			draw/rotation.c											\
		controls/loop_hook.c	controls/key_hook.c										\
		init/init.c				init/info.c												\
		exit.c
SRC_DIR =	srcs/

#	Objects
OBJ_DIR =	objs/
OBJS =		$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

#	Headers
HEADERS =		incs/fdf.h
HEADERS_PATH =	-I./incs -I$(LIBMLX_DIR)/include -I./libft/includes

#	Compiler
CC =		cc
CFLAGS +=	-Wall -Wextra -Werror -Ofast

LIBS =		$(LIBMLX) -ldl -lglfw -pthread -lm -L./libft -lft
##	Libs for MacOS:
#LIBS +=		-framework Cocoa -framework OpenGL -framework IOKit
LIBMLX_DIR =	./MLX42
LIBMLX = $(LIBMLX_DIR)/build/libmlx42.a
LIBMLX_GIT = https://github.com/codam-coding-college/MLX42.git

NAME =		fdf
LIBFT =		libft/libft.a

#	Colors
RED =		\033[0;31m
GREEN =		\033[0;32m
YELLOW =	\033[0;33m
ENDCOLOR =	\033[0m

#	Rules
all: $(NAME)

$(LIBFT): phony
	@make -C libft

$(LIBMLX):
	@if [ ! -d "$(LIBMLX_DIR)" ] || [ -z "$(ls -A $(LIBMLX_DIR))" ]; then \
		git clone $(LIBMLX_GIT) $(LIBMLX_DIR); \
	fi
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4
	@echo "$(GREEN)✅ MLX42: Library compiled.$(ENDCOLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS_PATH)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS_PATH) -o $(NAME)
	@echo "$(GREEN)✅ FdF: Compilation complete!$(ENDCOLOR)"

clean:
	@make -C ./libft clean
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)✅ FdF: Clean complete.$(ENDCOLOR)"

fclean:
	@make -C ./libft fclean
	@rm -rf $(OBJ_DIR) $(LIBMLX_DIR) $(NAME)
	@echo "$(RED)✅ FdF: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re phony
