/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:11:42 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/17 21:50:05 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_i = 0;

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	i = 0;

	g_i = 1;
	(void)info;
	(void)context;
	if (signum == SIGUSR2)
		i++;
	else if (signum == SIGUSR1)
		ft_printf("Bytes received: %d\n", i / 8);
}

void	wait_server(void)
{
	int	response;

	response = 0;
	while (g_i == 0)
	{
		usleep(100);
		if (++response == 50)
		{
			ft_printf("No response from server.\n");
			exit(1);
		}
	}
	g_i = 0;
}
void	send_signal(int pid, char *message)
{
	int	i;
	int	j;

	i = 0;
	while (message[i])
	{
		j = -1;
		while (++j < 8)
		{
			if ((message[i] & (1 << j)))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			wait_server();
		}
		i++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR2);
		wait_server();
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_id;

	if (argc != 3)
		return (printf("ERROR: Usage %s <PID> <MESSAGE>\n", argv[0]));
	server_id = ft_atoi(argv[1]);
	if (!server_id)
		return (printf("ERROR: First argument (%s) false.\n", argv[1]));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up handlers.\n");
		return (1);
	}
	if (!argv[2][0])
		return (printf("ERROR: Second argument is empty.\n"));
	send_signal(server_id, argv[2]);
	return (0);
}
