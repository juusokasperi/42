SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++11

NAME = easyFinder

%.o: %.cpp easyfind.hpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Enjoy \033[0;93m./$(NAME)\033[0m"

clean:
	@rm -rf $(OBJS)
	@echo "Clean \033[0;91mOK\033[0m"

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "Fclean \033[0;91mOK\033[0m"

re: fclean all

.PHONY: all clean fclean re
