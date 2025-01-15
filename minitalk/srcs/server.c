/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:49:27 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/15 14:43:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_signal(int pid, int signal, char *str);
static void	signal_handler(int signum, siginfo_t *info, void *context);
static void	handle_byte(t_buffer *buffer, int pid);

volatile sig_atomic_t	g_pid = 0;

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Error setting up handlers.");
	ft_printf("%sServer PID:%s %d\n", TYELLOW, TRESET, getpid());
	while (1)
		usleep(10);
	return (0);
}

// On macOS, the system reroutes the signal to pid 0 at times, especially
// when sending lots of signals rapidly. A workaround for that
// is to change line 53 to 'else if (g_pid != info->si_pid && info->si_pid)'.
// On Linux, this is not an issue.
static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_buffer	buffer = {0};
	int				pid;

	(void)context;
	if ((signum != SIGUSR1 && signum != SIGUSR2)
		|| (!info->si_pid && !g_pid))
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
		ft_signal(pid, SIGUSR2, buffer.str);
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
		ft_signal(pid, SIGUSR1, buffer->str);
		g_pid = 0;
	}
	else
		ft_signal(pid, SIGUSR2, buffer->str);
	buffer->received_char = 0;
	buffer->bit_count = 0;
}

static void	ft_signal(int pid, int signal, char *str)
{
	if (kill(pid, signal) == -1)
	{
		if (str)
			ft_free((void **)&str);
		ft_error("Problem with signal transmission.");
		g_pid = 0;
	}
}
