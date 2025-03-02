SRCS =		main.cpp	Weapon.cpp	HumanA.cpp	HumanB.cpp
OBJS =		$(SRCS:.cpp=.o)

CC =		c++
CFLAGS +=	-Wall -Wextra -Werror -I./ -std=c++98

NAME =		unnecessaryViolence

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


