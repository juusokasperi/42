SRCS =		main.cpp
OBJS =		main.o

CC =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++98

NAME = brain

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation OK, executable ./$(NAME)"

clean:
	@rm -rf $(OBJS)
	@echo "Clean OK."

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "FClean OK."

re: fclean all

.PHONY: all clean fclean re
