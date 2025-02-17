/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:18:42 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/15 14:39:26 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	execute_left(t_shell *sh, t_pipe *pipex)
{
	pid_t	pid;

	pid = create_fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (pipex->input_fd >= 0 && pipex->input_fd != STDIN_FILENO)
		{
			safe_dup2(pipex->input_fd, STDIN_FILENO);
			close_fd(pipex->input_fd);
		}
		safe_dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipex->pipe_fd);
		exit(execute_node(sh, pipex->node->data.binary.left, -1, -1));
	}
	return (pid);
}

static void	clean_redir_fds(t_redir *redir)
{
	while (redir)
	{
		if (redir->hd_preprocessed_fd != -1)
		{
			close_fd(redir->hd_preprocessed_fd);
			redir->hd_preprocessed_fd = -1;
		}
		redir = redir->next;
	}
}

pid_t	execute_right(t_shell *sh, t_pipe *pipex)
{
	pid_t	pid;

	clean_redir_fds(pipex->node->data.binary.left->data.command.redirects);
	pid = create_fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		safe_dup2(pipex->pipe_fd[0], STDIN_FILENO);
		close_pipe(pipex->pipe_fd);
		if (pipex->output_fd >= 0 && pipex->output_fd != STDOUT_FILENO)
		{
			safe_dup2(pipex->output_fd, STDOUT_FILENO);
			close_fd(pipex->output_fd);
		}
		exit(execute_node(sh, pipex->node->data.binary.right, -1, -1));
	}
	return (pid);
}
