#	Sources
SRCS =	main.c 								\
		interactive_mode.c					\
		noninteractive_mode.c				\
		init.c								\
		unclosed_quotes/unclosed_quotes.c	\
		unclosed_quotes/unclosed_quotes_utils.c	\
		lexer/lex.c							\
		lexer/lst_tools.c					\
		lexer/handlers.c					\
		lexer/handlers_2.c					\
		lexer/check_syntax.c				\
		astree/arg_lst.c					\
		astree/create_ast.c					\
		astree/free_ast.c					\
		astree/node_tools.c					\
		astree/parse.c						\
		astree/parse_redir_cmd_utils.c		\
		astree/parse_redir_cmd.c			\
		expansion/cmd/cmd_envs.c			\
		expansion/cmd/cmd_envs_split.c		\
		expansion/cmd/cmd_wildcard.c		\
		expansion/envs_main.c				\
		expansion/envs_utils.c				\
		expansion/wildcard_main.c			\
		expansion/wildcard_logic.c			\
		expansion/redir/redir_wildcard.c	\
		expansion/redir/redir_envs.c		\
		expansion/strip_quotes.c			\
		env/env_init.c						\
		env/env_tools.c						\
		env/lst_tools.c						\
		command/ft_pwd.c					\
		command/ft_echo.c					\
		command/ft_env.c					\
		command/ft_unset.c					\
		command/ft_export.c					\
		command/ft_cd.c						\
		command/ft_exit.c					\
		command/utils.c						\
		execution/error_handlers.c			\
		execution/path_utils.c				\
		execution/execute_external_cmd.c	\
		execution/execute_builtin.c			\
		execution/execute_node.c			\
		execution/execute_command.c			\
		execution/execute_logical.c			\
		execution/execute_pipe.c			\
		execution/pipe_helpper.c			\
		execution/pipe_child.c				\
		execution/execute_redirect.c		\
		execution/execute_subshell.c		\
		execution/handle_heredoc.c			\
		execution/execution_signals.c		\
		execution/convert_env_to_array.c	\
		execution/convert_cmd_to_array.c	\
		execution/expansion_handlers.c		\
		execution/pre_process_heredocs.c	\
		execution/termios_handlers.c		\
		debug/debug_print.c					\
		debug/debug_print_2.c				\
		utils/free_split.c					\
		utils/strjoin_quotes.c				\
		utils/print_error.c					\
		utils/strlen_no_escapes.c			\

SRCS_DIR =	srcs/

#	Objects
OBJS_DIR =	objs/
OBJS =		$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

#	Headers
HDR =		minishell.h
HDR_PATH =	incs/

#	Compiler
CC =		cc
INCS =		-I./incs/ -I./libft/includes/
CFLAGS +=	-Wall -Wextra -Werror $(INCS)
ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -g -fsanitize=address
endif
LDFLAGS =	-L./libft -lft -lreadline

########	macOS fix:
#	If compiling with macOS silicon, add readline library;
ifeq ($(shell uname -s)-$(shell uname -m), Darwin-arm64)
	RL_I =		-I/opt/homebrew/Cellar/readline/8.2.13/include
	RL_L =		-L/opt/homebrew/Cellar/readline/8.2.13/lib
	CFLAGS += 	$(RL_I)
	LDFLAGS +=	$(RL_L)
endif
########

#	Terminal colors
RED =		\033[0;31m
GREEN =		\033[0;32m
ENDCOLOR =	\033[0m

NAME =		minishell
LIBFT =		libft/libft.a

#	Rules
all: $(NAME)

bonus: all

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HDR_PATH)$(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): phony
	@make -C ./libft --no-print-directory

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ MINISHELL: Compilation complete!$(ENDCOLOR)"

debug: fclean $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ MINISHELL: FSanitize Compilation complete!$(ENDCOLOR)"

clean:
	@make -C ./libft clean --no-print-directory
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)✅ MINISHELL: Clean complete!$(ENDCOLOR)"

fclean:
	@make -C ./libft fclean --no-print-directory
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "$(RED)✅ MINISHELL: FClean complete!$(ENDCOLOR)"

re: fclean all

.PHONY: phony clean fclean re all bonus
