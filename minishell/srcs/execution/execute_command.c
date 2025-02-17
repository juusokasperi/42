/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:27:17 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/15 13:07:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_io(int input_fd, int output_fd)
{
	if (input_fd >= 0 && input_fd != STDIN_FILENO)
	{
		safe_dup2(input_fd, STDIN_FILENO);
		close_fd(input_fd);
	}
	if (output_fd >= 0 && output_fd != STDOUT_FILENO)
	{
		safe_dup2(output_fd, STDOUT_FILENO);
		close_fd(output_fd);
	}
}

static void	execute_child_process(t_shell *sh, t_node *node, t_fds *fds,
		t_builtin_type type)
{
	redirect_io(fds->input_fd, fds->output_fd);
	if (type == BUILTIN_FORK)
		exit(execute_builtin(sh, node));
	else
	{
		if (isatty(STDIN_FILENO) && restore_original_termios(sh) == -1)
			exit(1);
		if (signal(SIGINT, SIG_DFL) == SIG_ERR
			|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		{
			print_error(NULL, "signal", strerror(errno));
			exit(1);
		}
		execute_external_cmd(sh, node);
		handle_execve_error(NULL, node->data.command.args);
	}
}

static int	wait_child(pid_t pid, struct sigaction *old_sa_int)
{
	int	status;
	int	exit_status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exit_status = WTERMSIG(status) + 128;
		if (exit_status == 131)
			printf("Quit (core dumped)\n");
		else
			printf("\n");
	}
	restore_signals(old_sa_int);
	if (isatty(STDIN_FILENO) && disable_echo() == -1)
		return (1);
	return (exit_status);
}

int	execute_command(t_shell *sh, t_node *node, int input_fd, int output_fd)
{
	t_builtin_type		type;
	pid_t				pid;
	t_fds				fds;
	struct sigaction	old_sa_int;

	fds.input_fd = input_fd;
	fds.output_fd = output_fd;
	if (handle_expansions(sh, node) == -1)
		return (EXIT_FAILURE);
	if (!node->data.command.args)
		return (EXIT_SUCCESS);
	type = get_builtin_type(node->data.command.args->value);
	if (type == BUILTIN_NO_FORK)
		return (execute_builtin(sh, node));
	set_cmd_signals(&old_sa_int);
	pid = create_fork();
	if (pid < 0)
	{
		restore_signals(&old_sa_int);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
		execute_child_process(sh, node, &fds, type);
	return (wait_child(pid, &old_sa_int));
}
