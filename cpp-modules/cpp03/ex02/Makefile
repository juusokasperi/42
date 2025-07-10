SRCS =		ClapTrap.cpp	main.cpp	ScavTrap.cpp	FragTrap.cpp
OBJS = 		$(SRCS:.cpp=.o)

CC = 		c++
CFLAGS = 	-Wall -Wextra -Werror -std=c++98 -I./

NAME = fragTrap

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation ok, executable ./$(NAME)"

clean:
	@rm -rf $(OBJS)
	@echo "Clean OK"

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "Fclean OK"

re: fclean all

.PHONY: all clean fclean re
