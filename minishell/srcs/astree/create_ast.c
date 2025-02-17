/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:03:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 15:42:24 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_ast(t_token **tokens, t_error *lex_error)
{
	t_node	*root;

	root = parse_expressions(tokens);
	if (!root || (*tokens)->type != T_EOF)
	{
		*lex_error = SYNTAX_ERR;
		free_token_list(tokens);
		free_ast(root);
		return (NULL);
	}
	free_token_list(tokens);
	return (root);
}

t_node	*create_binary_node(t_node_type type, char *op)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->data.binary.left = NULL;
	node->data.binary.right = NULL;
	node->data.binary.operator = ft_strdup(op);
	if (!node->data.binary.operator)
	{
		ft_free((void **)&node);
		return (NULL);
	}
	return (node);
}

t_node	*create_subsh_node(t_node *subsh)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (free_ast(subsh));
	node->type = N_SUBSHELL;
	node->data.binary.left = subsh;
	node->data.binary.right = NULL;
	node->data.binary.operator = NULL;
	return (node);
}

t_node	*create_cmd_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = N_CMD;
	node->data.command.args = NULL;
	return (node);
}
