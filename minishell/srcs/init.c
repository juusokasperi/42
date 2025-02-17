/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:02:29 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/10 17:03:38 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signo);
static int	set_signals(void);

static int	set_termios(t_shell *sh)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		print_error(NULL, "tcgetattr", strerror(errno));
		return (-1);
	}
	sh->initial_term = term;
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
	{
		print_error(NULL, "tcgetattr", strerror(errno));
		return (-1);
	}
	return (0);
}

void	init_sh(t_shell *sh, char **env)
{
	if (isatty(STDIN_FILENO))
	{
		if (set_termios(sh) == -1 || set_signals() == -1)
			exit(1);
	}
	sh->env = init_env(sh, env);
	if (!sh->env)
		print_error("init_sh", "init_env",
			"Failed to initialize environment variables");
	sh->exit_status = 0;
	sh->exit = false;
}

static void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = SIGINT;
	}
}

static int	set_signals(void)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR
		|| signal (SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		print_error(NULL, "signal", strerror(errno));
		return (-1);
	}
	return (0);
}
