/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:21:32 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/31 17:48:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_expressions(t_token **tokens)
{
	t_node	*left;
	t_node	*binary_node;

	if ((*tokens)->type == T_PAREN_L)
		left = parse_parentheses(tokens);
	else
		left = parse_pipe(tokens);
	if (!left)
		return (NULL);
	while ((*tokens)->type == T_PIPE || (*tokens)->type == T_AND
		|| (*tokens)->type == T_OR)
	{
		binary_node = handle_pipe_and_or(tokens);
		if (!binary_node)
			return (free_ast(left));
		binary_node->data.binary.left = left;
		binary_node->data.binary.right = parse_expressions(tokens);
		if (!binary_node->data.binary.right)
			return (free_ast(binary_node));
		left = binary_node;
	}
	return (left);
}

t_node	*parse_pipe(t_token **tokens)
{
	t_node	*left;
	t_node	*pipe_node;

	left = parse_redir_or_cmd(tokens);
	if (!left)
		return (NULL);
	while ((*tokens)->type == T_PIPE)
	{
		pipe_node = create_binary_node(N_PIPE, (*tokens)->value);
		if (!pipe_node)
			return (free_ast(left));
		consume_token(tokens);
		pipe_node->data.binary.left = left;
		pipe_node->data.binary.right = parse_expressions(tokens);
		if (!pipe_node->data.binary.right)
			return (free_ast(pipe_node));
		left = pipe_node;
	}
	return (left);
}

t_node	*parse_simple_cmd(t_token **tokens)
{
	t_node	*cmd_node;

	cmd_node = create_cmd_node();
	while ((*tokens)->type == T_WORD)
	{
		if (argadd_back(&cmd_node->data.command.args,
				arglst_new((*tokens)->value)))
			return (free_ast(cmd_node));
		consume_token(tokens);
	}
	return (cmd_node);
}
