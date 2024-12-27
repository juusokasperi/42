/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:49:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/27 16:50:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_signal(int pid, int signal, char *str);
static void	signal_handler(int signum, siginfo_t *info, void *context);
static void	handle_byte(int *received_char, int *bit_count,
				t_buffer *buffer, int pid);

volatile sig_atomic_t	g_pid = 0;

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Error setting up handlers.");
	ft_printf("%sServer PID:%s %d\n", TYELLOW, TRESET, getpid());
	while (1)
		usleep(200);
	return (0);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		received_char = 0;
	static int		bit_count = 0;
	static t_buffer	buffer = {0};

	(void)context;
	if (!info->si_pid)
		return ;
	if (!g_pid)
		g_pid = info->si_pid;
	else if (g_pid != info->si_pid)
		return ;
	if (signum == SIGUSR1)
		received_char |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
		handle_byte(&received_char, &bit_count, &buffer, info->si_pid);
	else
		ft_signal(g_pid, SIGUSR2, buffer.str);
}

static void	clear_buffer(t_buffer *buffer)
{
	buffer->str = ft_free((void **)&buffer->str);
	buffer->size = 0;
	buffer->index = 0;
}

static void	handle_byte(int *received_char, int *bit_count,
	t_buffer *buffer, int pid)
{
	if (buffer->index >= buffer->size)
	{
		buffer->size += BUFFER_SIZE;
		buffer->str = ft_realloc((void *)buffer->str,
				buffer->size - BUFFER_SIZE, buffer->size);
		if (!buffer->str)
			ft_error("Malloc error.");
	}
	buffer->str[buffer->index++] = (char)*received_char;
	if (*received_char == '\0')
	{
		if (buffer->str)
			ft_printf("%s\n", buffer->str);
		clear_buffer(buffer);
		if (pid != 0)
		{
			ft_signal(pid, SIGUSR1, buffer->str);
			g_pid = 0;
		}
	}
	else if (pid != 0)
		ft_signal(pid, SIGUSR2, buffer->str);
	*received_char = 0;
	*bit_count = 0;
}

static void	ft_signal(int pid, int signal, char *str)
{
	if (kill(pid, signal) == -1)
	{
		if (str)
			ft_free((void **)&str);
		ft_error("Problem with signal transmission.");
	}
}
