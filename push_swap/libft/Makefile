LIBFT_SRCS := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c ft_free.c ft_count_digits.c ft_ltoa.c
LIBFT_PATH := $(addprefix ./srcs/libft/, $(LIBFT_SRCS))

PF_SRCS := ft_printf.c ft_printf_utils.c
PF_PATH := $(addprefix ./srcs/ft_printf/, $(PF_SRCS))

GN_SRCS := get_next_line.c
GN_PATH := $(addprefix ./srcs/get_next_line/, $(GN_SRCS))

O_LIB := $(LIBFT_PATH:.c=.o)
O_PF := $(PF_PATH:.c=.o)
O_GN := $(GN_PATH:.c=.o)

HDR := libft.h ftprintf.h get_next_line.h
HDR_PATH := $(addprefix ./includes/, $(HDR))

CC := cc
CFLAGS += -Wall -Wextra -Werror -I./includes/
ARFLAGS := -rcs

RED = \033[0;31m
GREEN = \033[0;32m
ENDCOLOR = \033[0m

NAME := libft.a

all: $(NAME)

%.o: %.c $(HDR_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(O_LIB) $(O_PF) $(O_GN)
	ar $(ARFLAGS) $(NAME) $^
	@echo "$(GREEN)✅ LIBFT: Library compilation complete!$(ENDCOLOR)"

clean:
	rm -f $(O_LIB) $(O_PF) $(O_GN)
	@echo "$(RED)✅ LIBFT: Clean complete.$(ENDCOLOR)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)✅ LIBFT: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all
