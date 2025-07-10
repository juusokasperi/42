/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:43:11 by phuocngu          #+#    #+#             */
/*   Updated: 2025/01/30 16:21:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_args *cmd)
{
	t_args	*arg;
	bool	newline;
	int		ret;

	newline = true;
	arg = cmd->next;
	ret = 0;
	if (arg && ft_strcmp(arg->value, "-n") == 0)
	{
		newline = false;
		arg = arg->next;
	}
	while (arg && ret != -1)
	{
		ret = ft_putstr_fd(arg->value, STDOUT_FILENO);
		if (arg->next && ret != -1)
			ret = ft_putchar_fd(' ', STDOUT_FILENO);
		arg = arg->next;
	}
	if (newline && ret != -1)
		ret = ft_putchar_fd('\n', STDOUT_FILENO);
	if (ret == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
