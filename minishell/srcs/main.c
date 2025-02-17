/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:59:59 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/10 23:32:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	(void)argv;
	(void)env;
	if (argc != 1)
		print_error(NULL, NULL, "does not accept any arguments.");
	init_sh(&sh, env);
	if (isatty(STDIN_FILENO))
	{
		interactive_mode(&sh);
		restore_original_termios(&sh);
		rl_clear_history();
	}
	else
		noninteractive_mode(&sh);
	free_env_list(sh.env);
	return (sh.exit_status);
}
