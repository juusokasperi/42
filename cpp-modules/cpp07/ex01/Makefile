SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -I./ -std=c++98

NAME = iterFunc

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compiled, exec ./$(NAME)"

clean:
	@rm -rf $(OBJS)
	@echo "Clean ok"

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "FClean ok"

re: fclean all

.PHONY: all clean fclean re
