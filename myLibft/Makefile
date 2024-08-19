S := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c

PF_SRCS := ft_ltoa.c ft_printf.c ft_xtoa.c helper_functions_2.c \
	helper_functions.c parse_flags.c print_hex.c print_nbr.c \
	print_ptr.c print_strchar.c print_unsigned.c
PF_PATH := $(addprefix ./ft_printf/, $(PF_SRCS))

GN_SRCS := get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

O := $(S:.c=.o)
O_PF := $(PF_PATH:.c=.o)
O_GN := $(GN_SRCS:.c=.o)

H := libft.h ftprintf.h get_next_line.h

CC := gcc
CFLAGS += -Wall -Wextra -Werror -I./
ARFLAGS := -rcs

RED = \033[0;91m
GREEN = \033[0;92m
ENDCOLOR = \033[0m

NAME := libft.a

all: $(NAME)

%.o: %.c $H
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $O $(O_PF) $(O_GN)
	ar $(ARFLAGS) $(NAME) $^
	@echo "$(GREEN)✅ LIBFT: Library compilation complete!$(ENDCOLOR)"

clean:
	rm -f $O $(O_PF) $(O_GN)
	@echo "$(RED)✅ LIBFT: Clean complete.$(ENDCOLOR)"

fclean: clean
	rm  -f $(NAME)
	@echo "$(RED)✅ LIBFT: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all
