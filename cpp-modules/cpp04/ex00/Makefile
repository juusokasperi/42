SRCS =		Animal.cpp main.cpp Dog.cpp Cat.cpp WrongCat.cpp WrongAnimal.cpp
OBJS =		$(SRCS:.cpp=.o)

CC =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++98 -I./

NAME = animal

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
