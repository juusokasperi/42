/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:39:09 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/15 14:10:29 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_input(char *delimiter);
static int	check_interrupt(int *sig, struct sigaction old_handler);
static void	read_heredoc(int *sig, struct sigaction *old_handler,
				char *delimiter, int fd);

int	handle_heredoc(t_redir *redir, int *new_in)
{
	int					pipe_fd[2];
	struct sigaction	old_handler;
	int					sig;

	sig = 0;
	if (set_hd_handler(&old_handler))
		return (1);
	if (create_pipe(pipe_fd) == -1)
		return (1);
	read_heredoc(&sig, &old_handler, redir->hd_delimit, pipe_fd[1]);
	close_fd(pipe_fd[1]);
	if (*new_in != STDIN_FILENO)
		close_fd(*new_in);
	if (sig == 130)
		close_fd(pipe_fd[0]);
	else
		*new_in = pipe_fd[0];
	if (sigaction(SIGINT, &old_handler, NULL) == -1)
		return (1);
	return (sig);
}

static void	read_heredoc(int *sig, struct sigaction *old_handler,
		char *delimiter, int fd)
{
	char	*line;

	while (42)
	{
		line = check_input(delimiter);
		if (check_interrupt(sig, *old_handler))
			break ;
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_free((void **)&line);
			break ;
		}
		ft_putendl_fd(line, fd);
		ft_free((void **)&line);
	}
}

static int	check_interrupt(int *sig, struct sigaction old_handler)
{
	if (g_signal)
	{
		if (sigaction(SIGINT, &old_handler, NULL) == -1)
			print_error(NULL, "sigaction", strerror(errno));
		g_signal = 0;
		*sig = 130;
		return (1);
	}
	return (0);
}

static char	*check_input(char *delimiter)
{
	char	*input;
	char	*input_no_nl;

	ft_putstr_fd("> ", STDOUT_FILENO);
	input = get_next_line(0);
	if (!input)
	{
		if (g_signal == SIGINT)
			ft_putstr_fd("^C\n", STDOUT_FILENO);
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			print_heredoc_error(delimiter);
		}
		return (NULL);
	}
	input_no_nl = ft_strndup(input, ft_strlen(input) - 1);
	ft_free((void **)&input);
	if (!input_no_nl)
		return (NULL);
	return (input_no_nl);
}
