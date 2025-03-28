SRCS = main.cpp Span.cpp
OBJS = $(SRCS:.cpp=.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++11

NAME = spanClass

%.o: %.cpp Span.hpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Enjoy your \033[0;94m./$(NAME)\033[0m"

clean:
	@rm -rf $(OBJS)
	@echo "Clean ok."

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "FClean ok."

re: fclean all

.PHONY: all clean fcleean re
