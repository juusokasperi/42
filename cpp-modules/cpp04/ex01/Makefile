SRCS =		Animal.cpp main.cpp Dog.cpp Cat.cpp WrongCat.cpp WrongAnimal.cpp \
			Brain.cpp
OBJS =		$(SRCS:.cpp=.o)

CC =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++98 -I./ -g -fsanitize=address

NAME = animalWithBrain

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
