/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process_heredocs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:42:29 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/15 13:42:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_command_node(t_node *node)
{
	t_redir	*redir;
	int		heredoc_exit;

	redir = node->data.command.redirects;
	while (redir)
	{
		if (redir->type != T_HEREDOC)
		{
			redir = redir->next;
			continue ;
		}
		if (redir->hd_preprocessed_fd >= 0)
		{
			redir = redir->next;
			continue ;
		}
		heredoc_exit = handle_heredoc(redir, &redir->hd_preprocessed_fd);
		if (heredoc_exit != 0)
			return (heredoc_exit);
		redir = redir->next;
	}
	return (0);
}

int	pre_process_heredocs(t_shell *sh, t_node *node)
{
	int	heredoc_exit;

	if (!node)
		return (0);
	if (node->type == N_CMD)
		return (process_command_node(node));
	if (node->type == N_PIPE)
	{
		heredoc_exit = pre_process_heredocs(sh, node->data.binary.left);
		if (heredoc_exit != 0)
			return (heredoc_exit);
		return (pre_process_heredocs(sh, node->data.binary.right));
	}
	if (node->type == N_SUBSHELL)
		return (pre_process_heredocs(sh, node->data.binary.left));
	return (0);
}
