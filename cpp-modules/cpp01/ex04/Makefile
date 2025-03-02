SRCS =		main.cpp
OBJS =		$(SRCS:.cpp=.o)

CC =		c++
CFLAGS +=	-Wall -Wextra -Werror -std=c++98

NAME = sed

RED =		\033[0;91m
GREEN =		\033[0;92m
YELLOW =	\033[0;93m
ENDCOLOR =	\033[0m

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation $(GREEN)OK$(ENDCOLOR), executable $(YELLOW)./$(NAME)$(ENDCOLOR)"

clean:
	@rm -rf $(OBJS)
	@echo "Clean $(GREEN)OK.$(ENDCOLOR)"

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "FClean $(GREEN)OK.$(ENDCOLOR)"

re: fclean all

.PHONY: re all clean fclean
