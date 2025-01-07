#	Sources
SRCS =	main.c \
		read_map/read_map.c		read_map/read_map_utils.c	read_map/read_map_utils_2.c	\
		draw/draw.c				draw/draw_utils.c			draw/draw_utils_2.c			\
		controls/controls.c																\
		init/init.c				init/calculate.c										\
		exit.c
SRC_DIR =	srcs/

#	Objects
OBJ_DIR =	objs/
OBJS =		$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

#	Headers
HEADERS =		incs/fdf.h incs/terminal_colors.h
HEADERS_PATH =	-I./incs -I$(LIBMLX)/include -I./libft/includes

#	Compiler
CC =		cc
CFLAGS +=	-Wall -Wextra -Werror -Wunreachable-code -Ofast

##	Libs for MacOS:
#LIBS =		$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit -L./libft -lft
##	Libs for Linux:
LIBS =		$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L./libft -lft
LIBMLX =	./MLX42

NAME =		fdf
LIBFT =		libft/libft.a

#	Colors
RED =		\033[0;31m
GREEN =		\033[0;32m
ENDCOLOR =	\033[0m

#	Rules
all: $(NAME)

$(LIBFT): phony
	@make -C libft

libmlx: phony
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS_PATH)

$(NAME): $(LIBFT) libmlx $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS_PATH) -o $(NAME)
	@echo "$(GREEN)✅ FdF: Compilation complete!$(ENDCOLOR)"

clean:
	@make -C ./libft clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@echo "$(RED)✅ FdF: Clean complete.$(ENDCOLOR)"

fclean:
	@make -C ./libft fclean
	@rm -rf $(OBJ_DIR) $(LIBMLX)/build $(NAME) $(LIBFT)
	@echo "$(RED)✅ FdF: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re libmlx phony
