/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:49:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 12:04:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Add UTF-8 support! */

#include "minitalk.h"

void	expected_len(unsigned char *buffer, int *expected_bytes)
{
	if ((buffer[0] & 0x80) == 0)
		*expected_bytes = 1;
	else if ((buffer[0] & 0xE0) == 0xC0)
		*expected_bytes = 2;
	else if ((buffer[0] & 0xF0) == 0xE0)
		*expected_bytes = 3;
	else if ((buffer[0] & 0xF8) == 0xF0)
		*expected_bytes = 4;
	else
		*expected_bytes = 1;
}

void	print_handler(unsigned char *buffer, int *client_pid,
	int *expected_bytes, int *byte_count)
{
	int	i;

	if (buffer[0] == '\0')
	{
		ft_printf("\n");
		kill(*client_pid, SIGUSR1);
		*client_pid = 0;
	}
	else
	{
		i = 0;
		while (i < *expected_bytes)
			ft_printf("%c", buffer[i++]);
		kill(*client_pid, SIGUSR2);
	}
	i = 0;
	while (i < 4)
		buffer[i++] = 0;
	*byte_count = 0;
	*expected_bytes = 0;
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int				client_pid = 0;
	static unsigned char	buffer[4] = {0};
	static int				byte_count = 0;
	static int				bit_count = 0;
	static int				expected_bytes = 0;

	if (!client_pid)
		client_pid = info->si_pid;
	(void)context;
	if (signum == SIGUSR1)
		buffer[byte_count] |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		bit_count = 0;
		byte_count++;
		if (byte_count == 1)
			expected_len(buffer, &expected_bytes);
		if (byte_count == expected_bytes)
			print_handler(buffer, &client_pid, &expected_bytes, &byte_count);
		else
			kill(client_pid, SIGUSR2);
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
	ft_printf("------------------------------\n");
	ft_printf("* Welcome to Juuso's server! *\n");
	ft_printf("*       Server ID: %-10d*\n", getpid());
	ft_printf("------------------------------\n\n");
	while (1)
		pause();
	return (0);
}
