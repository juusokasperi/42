/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:06:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/17 15:33:19 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_sigint(t_error *exit_status);
static char	*check_input(t_error *lex_error, t_error *exit_status);
static void	free_input_and_ast(char **input, t_node *node);
static void	build_ast_and_execute(t_shell *sh, t_token **tokens, t_error *err);

void	interactive_mode(t_shell *sh)
{
	t_lexer	lex;

	sh->ast = NULL;
	while (sh->exit == false)
	{
		lex.error = 0;
		lex.input = check_input(&lex.error, &sh->exit_status);
		if (lex.error == MALLOC_ERR || lex.error == INTERRUPTED)
			continue ;
		check_sigint(&sh->exit_status);
		if (!(lex.input))
			break ;
		lexer(&lex);
		check_syntax(&lex);
		if (lex.error)
			sh->exit_status = lex.error;
		else if (lex.tokens)
			build_ast_and_execute(sh, &lex.tokens, &lex.error);
		free_input_and_ast(&lex.input, sh->ast);
	}
	if (sh->exit)
		ft_putstr_fd("exit\n", STDIN_FILENO);
}

//	if (!input) checks for Ctrl+D which will break out of the loop
//	if (input[0]) checks that we don't pass empty strings to history
static char	*check_input(t_error *lex_error, t_error *exit_status)
{
	char	*input;
	char	quote;

	input = readline(MSH);
	if (!input)
	{
		printf("\033[F\033[%zuCexit\n", strlen_no_escapes(MSH));
		return (NULL);
	}
	if (has_unclosed_quotes(input, &quote))
		hold_for_more_input(&input, &quote, lex_error);
	if (input && input[0])
		add_history(input);
	if (*lex_error)
		*exit_status = *lex_error;
	if (!input)
		return (NULL);
	return (input);
}

static void	build_ast_and_execute(t_shell *sh, t_token **tokens, t_error *err)
{
	sh->ast = create_ast(tokens, err);
	sh->exit_status = execute_node(sh, sh->ast, -1, -1);
}

static void	free_input_and_ast(char **input, t_node *node)
{
	ft_free((void **)input);
	free_ast(node);
}

//	If user has pressed ctrl+c in interactive mode,
//	exit_status needs to be set to 1.
static void	check_sigint(t_error *exit_status)
{
	if (g_signal == SIGINT)
	{
		*exit_status = 1;
		g_signal = 0;
	}
}
