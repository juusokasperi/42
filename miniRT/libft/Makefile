#	Sources
SRCS =	checks/ft_count_digits.c	checks/ft_isalnum.c		checks/ft_isalpha.c		\
		checks/ft_isascii.c			checks/ft_isdigit.c		checks/ft_isprint.c		\
		checks/ft_isspace.c			checks/ft_min.c			checks/ft_max.c			\
		conversion/ft_atoi.c		conversion/ft_itoa.c	conversion/ft_ltoa.c	\
		conversion/ft_tolower.c		conversion/ft_toupper.c	conversion/ft_abs.c		\
		conversion/ft_strtol.c														\
		ft_printf/ft_printf.c		ft_printf/ft_printf_utils.c						\
		get_next_line/get_next_line.c												\
		lists/ft_lstadd_back.c		lists/ft_lstadd_front.c	lists/ft_lstclear.c		\
		lists/ft_lstdelone.c		lists/ft_lstiter.c		lists/ft_lstlast.c		\
		lists/ft_lstmap.c			lists/ft_lstnew.c		lists/ft_lstsize.c		\
		mem/ft_bzero.c				mem/ft_calloc.c			mem/ft_free.c			\
		mem/ft_memchr.c				mem/ft_memcmp.c			mem/ft_memcpy.c			\
		mem/ft_memmove.c			mem/ft_memset.c			mem/ft_realloc.c		\
		puts/ft_putchar_fd.c		puts/ft_putendl_fd.c	puts/ft_putnbr_fd.c		\
		puts/ft_putstr_fd.c															\
		str/ft_split.c				str/ft_strchr.c			str/ft_strcmp.c			\
		str/ft_strdup.c				str/ft_striteri.c		str/ft_strjoin.c		\
		str/ft_strlcat.c			str/ft_strlcpy.c		str/ft_strlen.c			\
		str/ft_strmapi.c			str/ft_strncmp.c		str/ft_strnstr.c		\
		str/ft_strrchr.c			str/ft_strtrim.c		str/ft_substr.c			\
		error/ft_error.c

SRC_DIR = srcs/

#	Objects
OBJ_DIR =	objs/
OBJS =		$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

#	Headers
HDR =		libft.h ftprintf.h get_next_line.h
HDR_PATH =	$(addprefix ./includes/, $(HDR))

#	Compiler
CC =		cc
CFLAGS +=	-Wall -Wextra -Werror -I./includes/
ARFLAGS :=	-rcs

#	Terminal colors
RED =		\033[0;31m
GREEN =		\033[0;32m
ENDCOLOR =	\033[0m

NAME = libft.a

#	Rules
all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar $(ARFLAGS) $(NAME) $^
	@echo "$(GREEN)✅ LIBFT: Library compilation complete!$(ENDCOLOR)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)✅ LIBFT: Clean complete.$(ENDCOLOR)"

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo "$(RED)✅ LIBFT: FClean complete.$(ENDCOLOR)"

re: fclean all

.PHONY: clean fclean re all
