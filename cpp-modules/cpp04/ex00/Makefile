SRCS =		Animal.cpp main.cpp Dog.cpp Cat.cpp WrongCat.cpp WrongAnimal.cpp
SRCS_DIR =	srcs/

OBJS =		$(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
OBJS_DIR =	objs/

CC =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++98 -I./incs/

NAME = animal

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\nAll done, executable \033[0;92m./$(NAME)\033[0m"

clean:
	@rm -rf $(OBJS_DIR)

fclean:
	@rm -rf $(OBJS_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re
