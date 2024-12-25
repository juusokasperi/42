/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:49:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/25 17:18:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	ft_signal(int pid, int signal);
static void	expected_len(unsigned char *buffer, int *expected_bytes);
void		print_handler(t_signal_state *state);
void		signal_handler(int signum, siginfo_t *info, void *context);

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("ERROR: Error setting up handlers.");
	ft_printf("------------------------------\n");
	ft_printf("* Welcome to Juuso's server! *\n");
	ft_printf("*       Server ID: %d*\n", getpid());
	ft_printf("------------------------------\n\n");
	while (1)
		pause();
	return (0);
}

static void	ft_signal(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		ft_error("ERROR: Problem with signal transmission.\n");
}

static void	expected_len(unsigned char *buffer, int *expected_bytes)
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
		ft_signal(state->client_pid, SIGUSR1);
		state->client_pid = 0;
	}
	else
	{
		i = 0;
		while (i < state->expected_bytes)
			ft_printf("%c", state->buffer[i++]);
		ft_signal(state->client_pid, SIGUSR2);
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

	(void)context;
	if (!state.client_pid)
		state.client_pid = info->si_pid;
	else if (state.client_pid != info->si_pid)
		return ;
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
			ft_signal(state.client_pid, SIGUSR2);
	}
	else
		ft_signal(state.client_pid, SIGUSR2);
}
