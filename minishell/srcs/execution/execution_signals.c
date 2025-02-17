/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:17:35 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/09 18:39:33 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_signal_handler(int signum, siginfo_t *info, void *context);

int	set_hd_handler(struct sigaction *old_handler)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_sigaction = heredoc_signal_handler;
	if (sigaction(SIGINT, NULL, old_handler) == -1 || sigaction(SIGINT, &sa,
			NULL) == -1)
	{
		print_error(NULL, "sigaction", strerror(errno));
		return (-1);
	}
	return (0);
}

//	Set SIGINT to be ignored in the parent process,
//	and store the old SIGINT handler so it can be restored later after
//	the child process is done.
int	set_cmd_signals(struct sigaction *old_sa_int)
{
	if (sigaction(SIGINT, NULL, old_sa_int) == -1
		|| signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		print_error("set_cmd_signals", "sigaction", NULL);
		return (-1);
	}
	return (0);
}

//	After child process has run, restore the old SIGINT handler.
int	restore_signals(struct sigaction *old_sa_int)
{
	if (sigaction(SIGINT, old_sa_int, NULL) == -1)
	{
		print_error(NULL, "sigaction", strerror(errno));
		return (-1);
	}
	return (0);
}

static void	heredoc_signal_handler(int signum, siginfo_t *info, void *context)
{
	g_signal = signum;
	(void)info;
	(void)context;
}
