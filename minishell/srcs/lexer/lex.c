/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:25:04 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/09 15:48:47 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	input_handling_loop(t_lexer *lex, t_error *exit_s);
static void	init_lexer(t_lexer *lex);

void	lexer(t_lexer *lex)
{
	t_error	*exit_s;

	init_lexer(lex);
	exit_s = &(lex->error);
	if (!lex->input[0])
		return ;
	while (lex->input[lex->i])
	{
		input_handling_loop(lex, exit_s);
		if (*exit_s)
			return (free_token_list(&lex->tokens));
	}
	if (tokenadd_back(&lex->tokens, tokenlst_new(T_EOF, "newline")))
		*exit_s = MALLOC_ERR;
	if (!(*exit_s) && lex->paren_c != 0)
	{
		print_error(NULL, NULL, "syntax error near unexpected token `('");
		*exit_s = SYNTAX_ERR;
	}
	if (*exit_s)
		free_token_list(&lex->tokens);
}

static void	input_handling_loop(t_lexer *lex, t_error *exit_s)
{
	while (lex->input[lex->i] && ft_isspace(lex->input[lex->i]))
		lex->i++;
	if (!lex->input[lex->i])
		return ;
	if (lex->input[lex->i] == '>' || lex->input[lex->i] == '<')
		handle_redir(lex, exit_s);
	else if (lex->input[lex->i] == '|')
		handle_pipe_or(lex, exit_s);
	else if (lex->input[lex->i] == '(' || lex->input[lex->i] == ')')
		handle_parentheses(lex, exit_s);
	else if (lex->input[lex->i] == '&' && lex->input[lex->i + 1] == '&')
		handle_and(lex, exit_s);
	else
		handle_word(lex, exit_s);
}

static void	init_lexer(t_lexer *lex)
{
	lex->error = 0;
	lex->i = 0;
	lex->tokens = NULL;
	lex->paren_c = 0;
}
