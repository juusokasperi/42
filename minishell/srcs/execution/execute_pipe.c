/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:18:36 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/15 13:40:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_pipe(t_pipe *pipex, t_node *node, int input_fd, int output_fd)
{
	pipex->node = node;
	pipex->input_fd = input_fd;
	pipex->output_fd = output_fd;
	if (create_pipe(pipex->pipe_fd) == -1)
		return (-1);
	return (0);
}

static void	cleanup_parent(t_pipe *pipex)
{
	close_pipe(pipex->pipe_fd);
	if (pipex->input_fd >= 0)
		close_fd(pipex->input_fd);
	if (pipex->output_fd >= 0)
		close_fd(pipex->output_fd);
}

static int	wait_children(t_pipe *pipex)
{
	waitpid(pipex->left_pid, &pipex->status_left, 0);
	waitpid(pipex->right_pid, &pipex->status_right, 0);
	if (WIFEXITED(pipex->status_right))
		return (WEXITSTATUS(pipex->status_right));
	else
		return (-1);
}

int	execute_pipe(t_shell *sh, t_node *node, int input_fd, int output_fd)
{
	t_pipe	pipex;
	int		exit_status;

	if (init_pipe(&pipex, node, input_fd, output_fd) == -1)
		return (-1);
	pipex.left_pid = execute_left(sh, &pipex);
	if (pipex.left_pid < 0)
		return (-1);
	pipex.right_pid = execute_right(sh, &pipex);
	if (pipex.right_pid < 0)
		return (-1);
	cleanup_parent(&pipex);
	exit_status = wait_children(&pipex);
	return (exit_status);
}
