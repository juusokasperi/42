/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:49:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/14 14:34:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	debug_pipe_node(t_shell *sh, t_node *node, int depth)
{
	printf("Pipe:\n");
	print_ast(sh, node->data.binary.left, depth + 1);
	print_ast(sh, node->data.binary.right, depth + 1);
}

static void	debug_logical_node(t_shell *sh, t_node *node, int depth)
{
	printf("Logical Operator: %s\n", node->data.binary.operator);
	print_ast(sh, node->data.binary.left, depth + 1);
	print_ast(sh, node->data.binary.right, depth + 1);
}

static void	debug_subshell_node(t_shell *sh, t_node *node, int depth)
{
	printf("Subshell (parentheses):\n");
	print_ast(sh, node->data.binary.left, depth + 1);
}

//	Prints out the created ASTree
void	print_ast(t_shell *sh, t_node *node, int depth)
{
	int		i;
	t_node	*copy_node;
	t_shell	*copy_sh;

	copy_sh = sh;
	copy_node = node;
	if (!copy_node)
		return ;
	i = -1;
	while (++i < depth)
		printf("  ");
	i = -1;
	if (copy_node->type == N_CMD)
		debug_cmd_node(copy_sh, copy_node, depth);
	else if (copy_node->type == N_PIPE)
		debug_pipe_node(copy_sh, copy_node, depth);
	else if (copy_node->type == N_LOGICAL_OP)
		debug_logical_node(copy_sh, copy_node, depth);
	else if (copy_node->type == N_SUBSHELL)
		debug_subshell_node(copy_sh, copy_node, depth);
	else
		printf("Unknown node.\n");
}

//	For debugging, prints out lexer tokens in the list.
void	print_tokens(t_token *tokens)
{
	t_token	*cur;
	int		i;

	i = 0;
	cur = tokens;
	while (cur)
	{
		printf("[%d]:\tType: %u\tValue: '%s'\n", i++,
			cur->type, cur->value);
		cur = cur->next;
	}
}
