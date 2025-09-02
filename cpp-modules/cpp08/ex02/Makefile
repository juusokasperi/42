SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++11

NAME = mutantStack

%.o: %.cpp MutantStack.hpp MutantStack.tpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Done! HF with \033[0;93m./$(NAME)\033[0m"

clean:
	@rm -rf $(OBJS)
	@echo "Clean ok."

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "FClean ok."

re: fclean all

.PHONY: all clean fclean re
