/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:49:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/17 22:23:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	client_pid = 0;
	static int	received_char = 0;
	static int	bit_count = 0;

	if (!client_pid)
		client_pid = info->si_pid;
	(void)context;
	if (signum == SIGUSR1)
		received_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		if (received_char == '\0')
		{
			ft_printf("\n");
			kill(client_pid, SIGUSR1);
			client_pid = 0;
		}
		else
		{
			ft_printf("%c", (char)received_char);
			kill(client_pid, SIGUSR2);
		}
		received_char = 0;
		bit_count = 0;
	}
	else
		kill(client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up handlers.\n");
		return (1);
	}
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
