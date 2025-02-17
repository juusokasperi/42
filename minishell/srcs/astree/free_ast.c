/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:43:51 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 15:44:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*free_ast(t_node *node)
{
	if (!node)
		return (NULL);
	if (node->type == N_PIPE || node->type == N_LOGICAL_OP
		|| node->type == N_SUBSHELL)
		free_binary_node(node);
	else if (node->type == N_CMD)
		free_cmd_node(node);
	return (NULL);
}

void	free_args(t_args *arg)
{
	t_args	*temp;

	if (!arg)
		return ;
	while (arg)
	{
		temp = arg->next;
		ft_free((void **)&arg->value);
		ft_free((void **)&arg);
		arg = temp;
	}
}

void	free_redirs(t_redir *redir)
{
	t_redir	*temp;

	if (!redir)
		return ;
	while (redir)
	{
		temp = redir->next;
		if (redir->type == T_HEREDOC)
		{
			ft_free((void **)&redir->hd_delimit);
			ft_free((void **)&redir->hd_content);
		}
		else
			ft_free((void **)&redir->file);
		ft_free((void **)&redir);
		redir = temp;
	}
}

void	free_cmd_node(t_node *node)
{
	if (!node)
		return ;
	free_args(node->data.command.args);
	free_redirs(node->data.command.redirects);
	ft_free((void **)&node);
}

void	free_binary_node(t_node *node)
{
	if (!node)
		return ;
	free_ast(node->data.binary.left);
	free_ast(node->data.binary.right);
	ft_free((void **)&node->data.binary.operator);
	ft_free((void **)&node);
}
