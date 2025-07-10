/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:12:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/09 15:49:13 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes(t_lexer *lex, t_error *exit_s);

void	handle_word(t_lexer *lex, t_error *exit_s)
{
	int		cmd_start;
	char	*word;

	cmd_start = lex->i;
	while (lex->input[lex->i])
	{
		if (lex->input[lex->i] == '"' || lex->input[lex->i] == '\'')
			handle_quotes(lex, exit_s);
		else if (ft_strchr("<>|() ", lex->input[lex->i]))
			break ;
		else if (lex->input[lex->i] == '&' && lex->input[lex->i + 1] == '&')
			break ;
		else
			(lex->i)++;
	}
	word = ft_substr(lex->input, cmd_start, lex->i - cmd_start);
	if (!word)
		*exit_s = MALLOC_ERR;
	if (!*exit_s && tokenadd_back(&lex->tokens, tokenlst_new(T_WORD, word)))
		*exit_s = MALLOC_ERR;
	ft_free((void **)&word);
}

static void	handle_quotes(t_lexer *lex, t_error *exit_s)
{
	char	quote_char;

	quote_char = lex->input[lex->i];
	(lex->i)++;
	while (lex->input[lex->i] && lex->input[lex->i] != quote_char)
		(lex->i)++;
	if (lex->input[lex->i] != quote_char)
	{
		if (quote_char == '\'')
			print_error(NULL, NULL, "syntax error: unexpected end of file");
		else
			print_error(NULL, NULL, "syntax error: unexpected end of file");
		*exit_s = SYNTAX_ERR;
		return ;
	}
	(lex->i)++;
}

void	handle_parentheses(t_lexer *lex, t_error *exit_s)
{
	if (lex->input[lex->i] == '(')
	{
		if (tokenadd_back(&lex->tokens, tokenlst_new(T_PAREN_L, "(")))
			*exit_s = MALLOC_ERR;
		(lex->paren_c)++;
	}
	else if (!(*exit_s) && lex->input[lex->i] == ')')
	{
		if (tokenadd_back(&lex->tokens, tokenlst_new(T_PAREN_R, ")")))
			*exit_s = MALLOC_ERR;
		(lex->paren_c)--;
		if (!(*exit_s) && lex->paren_c < 0)
		{
			print_error(NULL, NULL, "syntax error near unexpected token `)'");
			*exit_s = SYNTAX_ERR;
		}
	}
	(lex->i)++;
}
