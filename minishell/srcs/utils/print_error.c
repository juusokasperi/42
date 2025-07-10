/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:51:49 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/15 13:17:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *arg, char *error_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	print_unclosed_syntax_error(char quote)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
}

int	parse_error(char *str, t_error *exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	*exit_status = 258;
	return (1);
}

void	print_heredoc_error(char *delimiter)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file", STDERR_FILENO);
	if (delimiter)
	{
		ft_putstr_fd(" (wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')", STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}
