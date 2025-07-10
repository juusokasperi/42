/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:12:59 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/09 23:51:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirect(int input_fd, int *new_in, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(NULL, file, strerror(errno));
		return (-1);
	}
	if (*new_in != input_fd)
		close_fd(*new_in);
	*new_in = fd;
	return (0);
}

static int	handle_output_redirect(int output_fd, int *new_out,
		char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		print_error(NULL, file, strerror(errno));
		return (-1);
	}
	if (*new_out != output_fd)
		close_fd(*new_out);
	*new_out = fd;
	return (0);
}

static int	process_redirect(t_redir *redir, t_redir_fds *fds)
{
	if (redir->type == T_IN)
		return (handle_input_redirect(fds->input_fd, fds->new_in, redir->file));
	if (redir->type == T_TRUNCATE)
		return (handle_output_redirect(fds->output_fd, fds->new_out,
				redir->file, O_WRONLY | O_CREAT | O_TRUNC));
	if (redir->type == T_APPEND)
		return (handle_output_redirect(fds->output_fd, fds->new_out,
				redir->file, O_WRONLY | O_CREAT | O_APPEND));
	if (redir->type == T_HEREDOC)
	{
		if (redir->hd_preprocessed_fd < 0)
		{
			print_error("heredoc", NULL, "was not preprocessed.");
			return (-1);
		}
		if (*fds->new_in != fds->input_fd)
			close_fd(*fds->new_in);
		*fds->new_in = redir->hd_preprocessed_fd;
		return (0);
	}
	return (0);
}

static int	process_redirects(t_redir *redir, t_redir_fds *fds)
{
	int	result;

	result = 0;
	while (redir)
	{
		result = process_redirect(redir, fds);
		if (result < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	execute_redirect(t_shell *sh, t_node *node, int input_fd, int output_fd)
{
	int			status;
	t_redir_fds	fds;

	if (!node || node->type != N_CMD)
		return (EXIT_FAILURE);
	fds.input_fd = input_fd;
	fds.output_fd = output_fd;
	fds.new_in = &input_fd;
	fds.new_out = &output_fd;
	if (handle_redir_expansions(sh, node) == -1)
		return (EXIT_FAILURE);
	if (process_redirects(node->data.command.redirects, &fds) < 0)
		return (EXIT_FAILURE);
	status = execute_command(sh, node, *fds.new_in, *fds.new_out);
	if (*fds.new_in != fds.input_fd)
		close_fd(*fds.new_in);
	if (*fds.new_out != fds.output_fd)
		close_fd(*fds.new_out);
	return (status);
}
