S := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

S_BONUS := ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c  \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

O := $(S:.c=.o)
O_BONUS := $(S_BONUS:.c=.o)

H := libft.h

GREEN = \033[0;32m
RED = \033[0;31m
ENDCOLOR = \033[0m

CC := cc
CFLAGS += -Wall -Wextra -Werror -I./

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	ifeq ($(shell uname -p),arm)
		CFLAGS += -arch x86_64
	endif
endif

ARFLAGS := -rcs

NAME := libft.a

all: $(NAME)

%.o: %.c $H
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus

.bonus: $(NAME) $(O_BONUS)
	@ar $(ARFLAGS) $(NAME) $(O_BONUS)
	@touch .bonus
	@echo "$(GREEN)✅ LIBFT: Bonus compilation complete!$(ENDCOLOR)"

$(NAME): $O
	@ar $(ARFLAGS) $(NAME) $^
	@echo "$(GREEN)✅ LIBFT: Library compilation complete!$(ENDCOLOR)"

clean:
	@rm -f $O $(O_BONUS) .bonus
	@echo "$(RED)✅ LIBFT: Clean complete.$(ENDCOLOR)"

fclean: clean
	@rm  -f $O $(O_BONUS) .bonus $(NAME)
	@echo "$(RED)✅ LIBFT: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all bonus
