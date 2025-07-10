SRC = srcs/ft_display_file.c

OBJ = $(SRC:.c=.o)

HDR = ft_display_file.h
PATH_HDR = $(addprefix $(INCLUDES), $(HDR))
INCLUDES = ./includes/

GREEN = \033[0;92m
RED = \033[0;91m
ENDCOLOR = \033[0m

CC = gcc
CFLAGS += -Wall -Wextra -Werror -I$(INCLUDES)

NAME = ft_display_file

all: $(NAME)

%.o: %.c $(PATH_HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)✅ FT_DISPLAY_FILE: Compilation complete!$(ENDCOLOR)"

clean:
	rm -f $(OBJ)
	@echo "$(RED)✅ FT_DISPLAY_FILE: Clean done.$(ENDCOLOR)"


fclean:
	rm -f $(OBJ) $(NAME)
	@echo "$(RED)✅ FT_DISPLAY_FILE: Fclean done.$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re
