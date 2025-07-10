/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:40:58 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/09 18:34:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	After returning from child process, restore the terminal settings
//	that we use for minishell.
int	disable_echo(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		print_error(NULL, "tcgetattr", strerror(errno));
		return (-1);
	}
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
	{
		print_error(NULL, "tcgetattr", strerror(errno));
		return (-1);
	}
	return (0);
}

//	Before executing the external command, restore the original terminal
//	settings (that were in effect before first starting minishell), since
//	for minishell we have disabled printing of ctl characters and disabled
//	the quit character.
int	restore_original_termios(t_shell *sh)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &sh->initial_term) == -1)
	{
		print_error(NULL, "tcsetattr", strerror(errno));
		return (-1);
	}
	return (0);
}
