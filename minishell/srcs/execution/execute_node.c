/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:22:45 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/15 13:26:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_node(t_shell *sh, t_node *node, int input_fd, int output_fd)
{
	int	hd_return;

	if (!node)
		return (EXIT_SUCCESS);
	hd_return = pre_process_heredocs(sh, node);
	if (hd_return != 0)
		return (hd_return);
	if (node->type == N_CMD)
	{
		if (node->data.command.redirects)
			return (execute_redirect(sh, node, input_fd, output_fd));
		else
			return (execute_command(sh, node, input_fd, output_fd));
	}
	else if (node->type == N_PIPE)
		return (execute_pipe(sh, node, input_fd, output_fd));
	else if (node->type == N_LOGICAL_OP)
		return (execute_logical(sh, node, input_fd, output_fd));
	else if (node->type == N_SUBSHELL)
		return (execute_subshell(sh, node, input_fd, output_fd));
	else
		print_error(NULL, NULL,
			"Unrecognized node type encountered in execution.");
	return (EXIT_FAILURE);
}
