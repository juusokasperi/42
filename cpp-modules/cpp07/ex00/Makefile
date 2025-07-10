SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -I./ -std=c++98

NAME = templateFunctions

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compiled, executable ./$(NAME)"

clean:
	@rm -rf $(OBJS)
	@echo "Clean OK."

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "Fclean OK."

re: fclean all

.PHONY: re clean fclean all
