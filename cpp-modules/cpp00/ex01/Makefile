SRCS = main.cpp simpleClass.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = phonebook

CC = c++

INCS = -I./

CFLAGS += -Wall -Wextra -Werror -std=c++98 $(INCS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: re all clean fclean
