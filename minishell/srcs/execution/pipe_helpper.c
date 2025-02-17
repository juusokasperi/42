/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:35:53 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/09 14:58:52 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		print_error(NULL, "pipe", strerror(errno));
		return (-1);
	}
	return (0);
}

void	safe_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		print_error(NULL, "dup2", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int	create_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error(NULL, "fork", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	close_fd(int fd)
{
	if (fd >= 0)
	{
		if (close(fd) == -1)
		{
			print_error(NULL, "close", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
}

void	close_pipe(int fd[2])
{
	close_fd(fd[0]);
	close_fd(fd[1]);
}
