SRCS =		ClapTrap.cpp	main.cpp	ScavTrap.cpp	FragTrap.cpp \
			DiamondTrap.cpp

OBJS = 		$(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
OBJS_DIR =	objs/

HDR =		ClapTrap.hpp	ScavTrap.hpp	FragTrap.hpp	DiamondTrap.hpp

CC = 		c++
CFLAGS = 	-Wall -Wextra -Werror -std=c++98 -I./

NAME = diamondTrap

$(OBJS_DIR)%.o: %.cpp $(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HDR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation ok, executable ./$(NAME)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Clean OK"

fclean:
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "Fclean OK"

re: fclean all

.PHONY: all clean fclean re
