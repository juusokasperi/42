/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:11:42 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/27 01:03:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_signal(int pid, int signal);
static void	send_signal(int pid, char *message);

int	main(int argc, char **argv)
{
	int					server_id;

	if (argc != 3)
		ft_error("Usage ./client <PID> <MESSAGE>");
	server_id = ft_atoi(argv[1]);
	if (server_id <= 0 || kill(server_id, 0) == -1)
		ft_error("Incorrect server ID.");
	send_signal(server_id, argv[2]);
	return (0);
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
			usleep(50);
		}
		else
		{
			usleep(50);
			return ;
		}
	}
	ft_error("Problem with signal transmission.");
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
