CC = cc
NASM = nasm

SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
SRCS_DIR = srcs/

INCS = -I./incs/

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.s=.o))

BIN_DIR = bin/

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

all: tester

ensure_dir:
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.s ensure_dir
	$(NASM) $(ASMFLAGS) $(INCS) -MD $(@:.o=.d) -MP $< -o $@

-include $(DEPS)

tester: ensure_dir objs/main.o $(LIB)
	$(CC) -o $(BIN_DIR)tester objs/main.o $(LDFLAGS)

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)

objs/main.o: srcs/main.c ensure_dir
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(OBJS_DIR) $(BIN_DIR) $(LIB)


re: clean all

.PHONY: all clean re
