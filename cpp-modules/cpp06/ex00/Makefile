SRCS = ScalarConverter.cpp main.cpp
SRCS_DIR = srcs/

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

INCS_DIR = incs/

HDRS = $(INCS_DIR)ScalarConverter.hpp

INCS = -I./$(INCS_DIR)

CC = c++
CFLAGS = -Wall -Wextra -Werror $(INCS) -std=c++11

NAME = convert

YELLOW = \033[0;93m
ENDCOLOR = \033[0m

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Enjoy, executable $(YELLOW)./$(NAME)$(ENDCOLOR)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Clean ok."

fclean:
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "FClean ok."

re: fclean all

.PHONY: all clean fclean re
