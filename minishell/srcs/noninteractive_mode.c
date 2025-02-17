/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_mode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:19:02 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/15 12:50:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_input(t_error *lex_error, t_error *exit_status);
static void	free_input_and_ast(char **input, t_node *node);
static void	build_ast_and_execute(t_shell *sh, t_token **tokens, t_error *err);

void	noninteractive_mode(t_shell *sh)
{
	t_lexer	lex;

	sh->ast = NULL;
	while (sh->exit == false)
	{
		lex.error = 0;
		lex.input = check_input(&lex.error, &sh->exit_status);
		if (lex.error == MALLOC_ERR || lex.error == INTERRUPTED)
			continue ;
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
}

static char	*check_input(t_error *lex_error, t_error *exit_status)
{
	char	*input;
	char	quote;

	input = get_next_line(0);
	if (!input)
		return (NULL);
	if (has_unclosed_quotes(input, &quote))
		hold_for_more_input(&input, &quote, lex_error);
	if (*lex_error)
		*exit_status = *lex_error;
	clean_str(&input);
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
