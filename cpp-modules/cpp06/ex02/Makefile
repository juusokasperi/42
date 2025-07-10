SRCS = main.cpp Base.cpp
SRCS_DIR = srcs/

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

INCS_DIR = incs/

HDRS = A.hpp B.hpp C.hpp Base.hpp
HDRS_PATH = $(addprefix $(INCS_DIR), $(HDRS))

INCS = -I./$(INCS_DIR)

CC = c++
CFLAGS = -Wall -Wextra -Werror $(INCS) -std=c++11

NAME = theRealType

YELLOW = \033[0;93m
ENDCOLOR = \033[0m

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(HDRS_PATH)
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
