SRCS = Account.cpp tests.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = tester

CC = c++

INCS = -I./

CFLAGS += -Wall -Wextra -Werror $(INCS) -std=c++98

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation done."

clean:
	@rm -rf $(OBJS)
	@echo "Clean OK"

fclean:
	@rm -rf $(OBJS) $(NAME)
	@echo "FClean OK"

re: fclean all

.PHONY: all clean fclean re
