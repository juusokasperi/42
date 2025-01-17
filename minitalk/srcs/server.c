/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:49:27 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/17 11:39:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_signal(int pid, int signal, t_buffer *buffer);
static void	signal_handler(int signum, siginfo_t *info, void *context);
static void	handle_byte(t_buffer *buffer, int pid);

volatile sig_atomic_t	g_pid = 0;

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaddset(&sa.sa_mask, SIGUSR1) == -1
		|| sigaddset(&sa.sa_mask, SIGUSR2) == -1)
		ft_error("Error setting up sigset.");
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Error setting up handlers.");
	ft_printf("%sServer PID:%s %d\n", TYELLOW, TRESET, getpid());
	while (1)
		pause();
	return (0);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_buffer	buffer = {0};
	int				pid;

	(void)context;
	if (!info->si_pid && !g_pid)
		return ;
	if (!g_pid)
		g_pid = info->si_pid;
	else if (g_pid != info->si_pid)
		return ;
	pid = g_pid;
	if (signum == SIGUSR1)
		buffer.received_char |= (1 << (7 - buffer.bit_count));
	buffer.bit_count++;
	if (buffer.bit_count == 8)
		handle_byte(&buffer, pid);
	else
		ft_signal(pid, SIGUSR2, &buffer);
}

static void	clear_buffer(t_buffer *buffer)
{
	buffer->str = ft_free((void **)&buffer->str);
	buffer->size = 0;
	buffer->index = 0;
}

static void	handle_byte(t_buffer *buffer, int pid)
{
	if (buffer->index >= buffer->size)
	{
		buffer->size += BUFFER_SIZE;
		buffer->str = ft_realloc((void *)buffer->str,
				buffer->size - BUFFER_SIZE, buffer->size);
		if (!buffer->str)
			ft_error("Malloc error.");
	}
	buffer->str[buffer->index++] = (char)buffer->received_char;
	if (buffer->received_char == '\0')
	{
		if (buffer->str)
			ft_printf("%s\n", buffer->str);
		clear_buffer(buffer);
		ft_signal(pid, SIGUSR1, buffer);
		g_pid = 0;
	}
	else
		ft_signal(pid, SIGUSR2, buffer);
	buffer->received_char = 0;
	buffer->bit_count = 0;
}

static void	ft_signal(int pid, int signal, t_buffer *buffer)
{
	if (kill(pid, signal) == -1)
	{
		clear_buffer(buffer);
		buffer->received_char = 0;
		buffer->bit_count = 0;
		ft_printf("%sERROR:%s ", TRED, TRESET);
		ft_printf("Problem sending acknowledgement. ");
		ft_printf("State reset, server open for a new connection.\n");
		g_pid = 0;
	}
}
