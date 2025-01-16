/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:11:42 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/15 18:38:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);
static void	send_signal(int pid, char *message);
static void	wait_server(int *ack);
static void	ft_signal(int pid, int signal);

volatile sig_atomic_t	g_ack = 0;

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_id;

	if (argc != 3)
		ft_error("Usage ./client <PID> <MESSAGE>");
	server_id = ft_atoi(argv[1]);
	if (server_id <= 0 || kill(server_id, 0) == -1)
		ft_error("Incorrect server ID.");
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaddset(&sa.sa_mask, SIGUSR1) == -1
		|| sigaddset(&sa.sa_mask, SIGUSR2) == -1)
		ft_error("Error setting up sigset.");
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Error setting up handlers.");
	usleep(200);
	send_signal(server_id, argv[2]);
	return (0);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	bits_received = 0;

	(void)info;
	(void)context;
	if (signum == SIGUSR2 || signum == SIGUSR1)
	{
		g_ack = 1;
		if (signum == SIGUSR2)
			bits_received++;
		else if (signum == SIGUSR1)
			ft_printf("%sSUCCESS:%s %d bytes sent.\n",
				TGREEN, TRESET, bits_received / 8);
	}
	else
		ft_error("Invalid signal received.");
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
		ft_signal(pid, SIGUSR2);
}

static void	wait_server(int *ack)
{
	int	timeout;

	timeout = 0;
	usleep(DELAY);
	while (!g_ack && timeout < 50)
	{
		usleep(DELAY);
		timeout++;
	}
	if (g_ack)
		*ack = 1;
}

static void	ft_signal(int pid, int signal)
{
	int	retry;
	int	ack;

	ack = 0;
	retry = 0;
	while (retry < RETRY_LIMIT)
	{
		if (kill(pid, signal) != -1)
		{
			wait_server(&ack);
			if (ack)
			{
				g_ack = 0;
				return ;
			}
		}
		ft_printf("%sNo acknowledgement, retrying.%s\n", TYELLOW, TRESET);
		usleep(DELAY_LONG);
		retry++;
	}
	ft_error("Problem with signal transmission.");
}
