/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:14:29 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/15 13:49:17 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *sh)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (env->value)
		{
			if (printf("%s=%s\n", env->key, env->value) == -1)
				return (EXIT_FAILURE);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
