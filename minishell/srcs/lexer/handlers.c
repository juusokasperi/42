/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:10:09 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/02 22:14:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir(t_lexer *lex, t_error *exit_s)
{
	if (lex->input[lex->i] == '>' && lex->input[lex->i + 1] == '>')
	{
		if (tokenadd_back(&lex->tokens, tokenlst_new(T_APPEND, ">>")))
			*exit_s = MALLOC_ERR;
		lex->i += 2;
	}
	else if (lex->input[lex->i] == '>')
	{
		if (tokenadd_back(&lex->tokens, tokenlst_new(T_TRUNCATE, ">")))
			*exit_s = MALLOC_ERR;
		(lex->i)++;
	}
	else if (lex->input[lex->i] == '<' && lex->input[lex->i + 1] == '<')
	{
		if (tokenadd_back(&lex->tokens, tokenlst_new(T_HEREDOC, "<<")))
			*exit_s = MALLOC_ERR;
		lex->i += 2;
	}
	else if (lex->input[lex->i] == '<')
	{
		if (tokenadd_back(&lex->tokens, tokenlst_new(T_IN, "<")))
			*exit_s = MALLOC_ERR;
		(lex->i)++;
	}
}

void	handle_pipe_or(t_lexer *lex, t_error *exit_s)
{
	if (lex->input[lex->i + 1] == '|')
	{
		if (tokenadd_back(&lex->tokens, tokenlst_new(T_OR, "||")))
			*exit_s = MALLOC_ERR;
		lex->i += 2;
	}
	else
	{
		if (tokenadd_back(&lex->tokens, tokenlst_new(T_PIPE, "|")))
			*exit_s = MALLOC_ERR;
		(lex->i)++;
	}
}

void	handle_and(t_lexer *lex, t_error *exit_s)
{
	if (tokenadd_back(&lex->tokens, tokenlst_new(T_AND, "&&")))
		*exit_s = MALLOC_ERR;
	lex->i += 2;
}
