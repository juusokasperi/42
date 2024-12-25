/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:49:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/25 20:30:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_signal(int pid, int signal);
static void	signal_handler(int signum, siginfo_t *info, void *context);
static void	handle_byte(int *received_char, int *bit_count,
	int *client_pid, t_buffer *buffer);

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("ERROR: Error setting up handlers.");
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		client_pid = 0;
	static int		received_char = 0;
	static int		bit_count = 0;
	static t_buffer	buffer = {0};
	int				current_pid;

	(void)context;
	current_pid = info->si_pid;
	if (!client_pid)
		client_pid = current_pid;
	else if (client_pid != current_pid)
		return ;
	if (signum == SIGUSR1)
		received_char |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
		handle_byte(&received_char, &bit_count, &client_pid, &buffer);
	else
		ft_signal(client_pid, SIGUSR2);
}

static void	clear_buffer(t_buffer *buffer)
{
	buffer->str = ft_free((void **)&buffer->str);
	buffer->size = 0;
	buffer->index = 0;
}

static void	handle_byte(int *received_char, int *bit_count,
	int *client_pid, t_buffer *buffer)
{
	if (*received_char == '\0')
	{
		if (buffer->str)
		{
			ft_printf("%s\n", buffer->str);
			clear_buffer(buffer);
		}
		ft_signal(*client_pid, SIGUSR1);
		*client_pid = 0;
	}
	else
	{
		if (buffer->index >= buffer->size)
		{
			buffer->size += BUFFER_SIZE;
			buffer->str = ft_realloc((void *)buffer->str, buffer->size - BUFFER_SIZE, buffer->size);
			if (!buffer->str)
				ft_error("ERROR: Malloc error.");
		}
		buffer->str[buffer->index++] = (char)*received_char;
		ft_signal(*client_pid, SIGUSR2);
	}
	*received_char = 0;
	*bit_count = 0;
}

static void	ft_signal(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		ft_error("ERROR: Problem with signal transmission.");
}
