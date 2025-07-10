SRCS_DIR =	srcs/
SRCS =		AAnimal.cpp main.cpp Dog.cpp Cat.cpp WrongCat.cpp WrongAnimal.cpp \
			Brain.cpp

OBJS_DIR =	objs/
OBJS =		$(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

CC =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++98 -I./incs/

NAME = abstractAnimal

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\nHF, \033[0;92m./$(NAME)\033[0m"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Clean OK"

fclean:
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "Fclean OK"

re: fclean all

.PHONY: all clean fclean re
