SRCS =		main.cpp	Fixed.cpp	Point.cpp	bsp.cpp
OBJS =		$(SRCS:.cpp=.o)

CC =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++11 -I./

NAME =		triangleCheck

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
