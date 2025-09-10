SRCS = main.cpp BitcoinExchange.cpp
OBJS = $(SRCS:.cpp=.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++11

NAME = btc

%.o: %.cpp BitcoinExchange.hpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "HF with \033[0;93m./$(NAME)\033[0m"

clean:
	@rm -rf $(OBJS)
	@echo "Clean ok."

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "FClean ok."

re: fclean all

.PHONY: all clean fclean re
