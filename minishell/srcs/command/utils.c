/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:43:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/09 13:49:57 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Checks if ENV var is valid - has to start with a letters or underscore,
//	subsequent characters can also contain numbers.
int	valid_identifier(char *arg, char *command)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		print_error(command, arg, "not a valid identifier");
		return (0);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			print_error(command, arg, "not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}
