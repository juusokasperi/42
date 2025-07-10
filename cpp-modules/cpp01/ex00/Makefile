SRCS =		main.cpp	newZombie.cpp	randomChump.cpp	Zombie.cpp

OBJS =		$(SRCS:.cpp=.o)

CC =		c++
INCS =		-I./
CFLAGS =	-Wall -Wextra -Werror -std=c++98 $(INCS)

NAME =		zombie

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
