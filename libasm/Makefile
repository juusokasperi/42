CC = cc
NASM = nasm

SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
SRCS_DIR = srcs/

INCS = -I./incs/

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.s=.o))

BIN_DIR = bin/

NAME = $(BIN_DIR)tester

DEPS = $(OBJS:.o=.d)

CFLAGS = -Wall -g
ifeq ($(shell uname -m), arm64)
	ARCH_FLAGS = --target=x86_64-apple-darwin
	CFLAGS += $(ARCH_FLAGS)
	ASMFLAGS = -f macho64 -g
else
	ASMFLAGS = -f elf64 -g -F -dwarf
endif

LDFLAGS = -L. -lasm $(ARCH_FLAGS)

LIB = libasm.a

all: $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s
	@mkdir -p $(OBJS_DIR)
	$(NASM) $(ASMFLAGS) $(INCS) -MD $(@:.o=.d) -MP $< -o $@

-include $(DEPS)

$(NAME): objs/main.o $(LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ objs/main.o $(LDFLAGS)

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)

objs/main.o: srcs/main.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(OBJS_DIR) $(BIN_DIR) $(LIB)


re: fclean all

.PHONY: all clean re fclean
