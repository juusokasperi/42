/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:07:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/09 12:55:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_syntax_errors(t_lexer *lex);
static int	check_pipe_and_or(t_token *cur, int *pipe_start);
static int	check_parentheses(t_token *cur, t_token_type type);

int	check_syntax(t_lexer *lex)
{
	if (!lex->tokens)
		return (0);
	if (lex->tokens->type == T_EOF)
	{
		free_token_list(&lex->tokens);
		return (0);
	}
	if (lex->error)
		return (0);
	if (has_syntax_errors(lex))
	{
		free_token_list(&lex->tokens);
		return (0);
	}
	return (1);
}

static int	has_syntax_errors(t_lexer *lex)
{
	t_token			*cur;
	int				pipe_start;

	cur = (lex->tokens);
	pipe_start = 1;
	while (cur)
	{
		if (cur->type == T_PAREN_L || cur->type == T_PAREN_R)
			if (check_parentheses(cur, cur->type))
				return (parse_error(cur->value, &lex->error));
		if (cur->type == T_PIPE || cur->type == T_AND || cur->type == T_OR)
			if (check_pipe_and_or(cur, &pipe_start))
				return (parse_error(cur->value, &lex->error));
		if (cur->type == T_TRUNCATE || cur->type == T_HEREDOC
			|| cur->type == T_APPEND || cur->type == T_IN)
			if (cur->next->type != T_WORD)
				return (parse_error(cur->next->value, &lex->error));
		if (cur->type == T_WORD && cur->next && cur->next->type == T_PAREN_L)
			return (parse_error(cur->next->next->value, &lex->error));
		pipe_start = 0;
		cur = cur->next;
	}
	return (0);
}

static int	check_pipe_and_or(t_token *cur, int *pipe_start)
{
	t_token	*next;

	next = cur->next;
	if (*pipe_start || next->type == T_EOF)
		return (1);
	*pipe_start = 1;
	if (next->type == T_PIPE || next->type == T_AND || next->type == T_OR)
		return (1);
	return (0);
}

static int	check_parentheses(t_token *cur, t_token_type type)
{
	t_token	*next;

	next = cur->next;
	if (type == T_PAREN_L)
	{
		if (!next || next->type == T_PIPE || next->type == T_AND
			|| next->type == T_OR || next->type == T_PAREN_R)
			return (1);
	}
	if (type == T_PAREN_R)
	{
		if (next && next->type == T_WORD)
			return (1);
	}
	return (0);
}
