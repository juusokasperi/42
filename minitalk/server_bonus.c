/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:49:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/24 18:05:29 by jrinta-          ###   ########.fr       */
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

void	print_handler(t_signal_state *state)
{
	int	i;

	if (state->buffer[0] == '\0')
	{
		ft_printf("\n");
		kill(state->client_pid, SIGUSR1);
		state->client_pid = 0;
	}
	else
	{
		i = 0;
		while (i < state->expected_bytes)
			ft_printf("%c", state->buffer[i++]);
		kill(state->client_pid, SIGUSR2);
	}
	i = 0;
	while (i < 4)
		state->buffer[i++] = 0;
	state->byte_count = 0;
	state->expected_bytes = 0;
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_signal_state	state = {0};

	if (!state.client_pid)
		state.client_pid = info->si_pid;
	(void)context;
	if (signum == SIGUSR1)
		state.buffer[state.byte_count] |= (1 << (7 - state.bit_count));
	state.bit_count++;
	if (state.bit_count == 8)
	{
		state.bit_count = 0;
		state.byte_count++;
		state.total_bytes++;
		if (state.byte_count == 1)
			expected_len(state.buffer, &state.expected_bytes);
		if (state.byte_count == state.expected_bytes)
			print_handler(&state);
		else
			kill(state.client_pid, SIGUSR2);
	}
	else
		kill(state.client_pid, SIGUSR2);
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
	ft_printf("*       Server ID: %d*\n", getpid());
	ft_printf("------------------------------\n\n");
	while (1)
		pause();
	return (0);
}
