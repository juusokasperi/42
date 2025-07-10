/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:55:33 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/15 12:47:05 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quotes(char *input, char *quote)
{
	int		i;

	i = -1;
	*quote = 0;
	while (input[++i])
	{
		if (!*quote && (input[i] == '\"' || input[i] == '\''))
			*quote = input[i];
		else if (*quote == '\'' && input[i] == '\'')
			*quote = 0;
		else if (*quote == '\"' && input[i] == '\"')
			*quote = 0;
	}
	if (*quote)
		return (1);
	return (0);
}

int	set_gnl_handler(struct sigaction *sa, struct sigaction *old_handler)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sa->sa_sigaction = gnl_sig_handler;
	if (sigaction(SIGINT, NULL, old_handler) == -1
		|| sigaction(SIGINT, sa, NULL) == -1)
	{
		print_error(NULL, "sigaction", strerror(errno));
		return (-1);
	}
	return (0);
}

void	gnl_sig_handler(int signum, siginfo_t *info, void *context)
{
	g_signal = signum;
	(void)info;
	(void)context;
}

int	check_gnl_interrupt(char **line, t_error *err)
{
	if (g_signal)
	{
		g_signal = 0;
		ft_putstr_fd("^C\n", 1);
		if (*line)
			ft_free((void **)&line);
		*err = INTERRUPTED;
		return (1);
	}
	return (0);
}

void	clean_str(char **input)
{
	int		len;

	if (!*input)
		return ;
	len = ft_strlen(*input);
	if ((*input)[len - 1] == '\n')
		(*input)[len - 1] = 0;
}
