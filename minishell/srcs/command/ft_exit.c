/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:16:00 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/10 23:18:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_shell *sh, t_args *args)
{
	t_args	*arg;
	int		exit_status;

	if (!args || !args->next)
		exit_status = sh->exit_status;
	else
	{
		arg = args->next;
		if (!is_numeric(arg->value))
		{
			print_error(NULL, arg->value, "numeric argument required");
			exit_status = 2;
		}
		else if (arg->next)
		{
			print_error("exit", NULL, "too many arguments");
			exit_status = EXIT_FAILURE;
		}
		else
			exit_status = (unsigned char)ft_atoi(arg->value);
	}
	sh->exit = true;
	return (exit_status);
}
