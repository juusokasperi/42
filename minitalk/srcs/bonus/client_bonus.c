/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:11:42 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/25 17:17:23 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Add UTF-8 support! */

#include "minitalk_bonus.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);
static void	wait_server(void);
static void	ft_signal(int pid, int signal);
static void	send_signal(int pid, char *message);

static int	g_i = 0;

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_id;

	if (argc != 3)
		ft_error("ERROR: Usage ./client_bonus <PID> <MESSAGE>");
	server_id = ft_atoi(argv[1]);
	if (server_id <= 0 || kill(server_id, 0) == -1)
		ft_error("ERROR: Incorrect server ID.");
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("ERROR: Error setting up handlers.");
	send_signal(server_id, argv[2]);
	return (0);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
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

static void	wait_server(void)
{
	int	response;

	response = 0;
	while (g_i == 0)
	{
		usleep(100);
		if (++response == 50)
			ft_error("ERROR: No response from server.");
	}
	g_i = 0;
}

static void	ft_signal(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		ft_error("ERROR: Problem with signal transmission.");
}

static void	send_signal(int pid, char *message)
{
	int				i;
	int				j;
	unsigned char	byte;

	i = -1;
	while (message[++i])
	{
		byte = (unsigned char)message[i];
		j = 8;
		while (--j >= 0)
		{
			if ((byte >> j) & 1)
				ft_signal(pid, SIGUSR1);
			else
				ft_signal(pid, SIGUSR2);
			wait_server();
		}
	}
	i = 0;
	while (i++ < 8)
	{
		ft_signal(pid, SIGUSR2);
		wait_server();
	}
}
