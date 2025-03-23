SRCS = main.cpp Base.cpp A.cpp B.cpp C.cpp
SRCS_DIR = srcs/

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

INCS = -I./incs/

CC = c++
CFLAGS = -Wall -Wextra -Werror $(INCS) -std=c++11

NAME = theRealType

YELLOW = \033[0;93m
ENDCOLOR = \033[0m

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Enjoy executable $(YELLOW)./$(NAME)$(ENDCOLOR)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Clean OK."

fclean:
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "FClean OK."

re: fclean all

.PHONY: all clean fclean re
