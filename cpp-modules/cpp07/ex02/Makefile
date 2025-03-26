SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

H = Array.hpp Array.tpp

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++11 -I./

NAME = arrayTemplate

%.o: %.cpp $(H)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Enjoy your ./$(NAME)"

clean:
	@rm -rf $(OBJS)

fclean:
	@rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
