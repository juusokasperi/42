/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:01:19 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 15:44:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == T_IN || type == T_APPEND
		|| type == T_HEREDOC || type == T_TRUNCATE);
}

void	consume_token(t_token **tokens)
{
	t_token	*tmp;

	if (tokens && *tokens)
	{
		tmp = (*tokens)->next;
		ft_free((void **)&((*tokens)->value));
		ft_free((void **)&(*tokens));
		*tokens = tmp;
	}
}

t_node	*handle_pipe_and_or(t_token **tokens)
{
	t_node	*binary_node;

	if ((*tokens)->type == T_PIPE)
		binary_node = create_binary_node(N_PIPE, (*tokens)->value);
	else
		binary_node = create_binary_node(N_LOGICAL_OP, (*tokens)->value);
	if (!binary_node)
		return (NULL);
	consume_token(tokens);
	return (binary_node);
}

t_node	*parse_parentheses(t_token **tokens)
{
	t_node	*node;

	consume_token(tokens);
	node = parse_expressions(tokens);
	if (!node)
		return (NULL);
	node = create_subsh_node(node);
	if (!node)
		return (NULL);
	if ((*tokens)->type != T_PAREN_R)
		return (free_ast(node));
	consume_token(tokens);
	return (node);
}
