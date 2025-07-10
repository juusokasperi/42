/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:57:10 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/09 23:21:07 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_subshell(t_shell *sh, t_node *node, int input_fd, int output_fd)
{
	pid_t	pid;
	int		status;
	t_shell	copy_sh;

	copy_sh = *sh;
	pid = create_fork();
	if (pid == 0)
	{
		status = execute_node(&copy_sh, node->data.binary.left, input_fd,
				output_fd);
		if (status >= 0)
			exit(status);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
