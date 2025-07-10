SRCS = main.cpp PhoneBook.cpp Contact.cpp handleContacts.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = phoneBook

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
	@echo "Clean OK."

fclean:
	@rm -rf $(NAME) $(OBJS)
	@echo "FClean OK."

re: fclean all

.PHONY: re all clean fclean
