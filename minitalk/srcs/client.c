/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:11:42 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/25 19:34:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);
static void	wait_server(void);
static void	ft_signal(int pid, int signal);
static void	send_signal(int pid, char *message);

volatile sig_atomic_t g_ack = 0;

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_id;

	if (argc != 3)
		ft_error("ERROR: Usage ./client <PID> <MESSAGE>");
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
	(void)info;
	(void)context;
	if (signum == SIGUSR1 || signum == SIGUSR2)
		g_ack = 1;
}

static void	wait_server(void)
{
	int	response;

	response = 0;
	while (g_ack == 0)
	{
		usleep(DELAY);
		if (++response == 100)
			ft_error("ERROR: No acknowledgment from server.");
	}
	g_ack = 0;
}

static void	ft_signal(int pid, int signal)
{
	int	retry;

	retry = 0;
	while (retry < RETRY_LIMIT)
	{
		if (kill(pid, signal) == -1)
		{
			retry++;
			usleep(DELAY);
		}
		else
		{
			wait_server();
			return ;
		}
	}
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
		}
	}
	i = 0;
	while (i++ < 8)
	{
		ft_signal(pid, SIGUSR2);
	}
}
