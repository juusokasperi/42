SRCS_DIR = srcs/
SRCS = Bureaucrat.cpp main.cpp Form.cpp
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

INCS = -I./incs

CC = c++
CFLAGS += -Wall -Wextra -Werror -std=c++11 $(INCS)

NAME = bureaucratForm

GREEN = 	\033[0;92m
YELLOW = 	\033[1;93m
ENDCOLOR = 	\033[0m

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation $(GREEN)OK$(ENDCOLOR), executable $(YELLOW)./$(NAME)$(ENDCOLOR)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Clean $(GREEN)OK$(ENDCOLOR)"

fclean:
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "FClean $(GREEN)OK$(ENDCOLOR)"

re: fclean all

.PHONY: all clean fclean re
