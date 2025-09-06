SRCS = main.cpp
SRCS_DIR = srcs/

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++11 -I./$(INCS_DIR)

INCS = $(INCS_DIR)PmergeMe.hpp $(INCS_DIR)PmergeMe.tpp
INCS_DIR = incs/

NAME = PmergeMe

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(INCS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compiled! Executable \033[0;92m./$(NAME)\033[0m"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Clean ok."

fclean:
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "FClean ok."

re: fclean all

.PHONY: all clean fclean re
