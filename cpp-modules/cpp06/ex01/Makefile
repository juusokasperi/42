SRCS = main.cpp Serializer.cpp
SRCS_DIR = srcs/

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

INCS_DIR = incs/

HDRS = Data.hpp Serializer.hpp
HDRS_PATH = $(addprefix $(INCS_DIR), $(HDRS))

INCS = -I./$(INCS_DIR)

CC = c++
CFLAGS = -Wall -Wextra -Werror $(INCS) -std=c++11

NAME = serializer

YELLOW = \033[0;93m
ENDCOLOR = \033[0m

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(HDRS_PATH)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Enjoy executable $(YELLOW)./$(NAME)$(ENDCOLOR)"

clean:
	@rm -rf $(OBJS)
	@echo "Clean OK."

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "FClean OK."

re: fclean all

.PHONY: all clean fclean re
