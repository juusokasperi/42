/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:46:43 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 15:46:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_env_variable(t_env **env, char *variable);
static void	increment_shlvl(t_env *env);

// Split env by '=', add to list sh->env
t_env	*init_env(t_shell *sh, char **env)
{
	sh->env = NULL;
	while (*env)
	{
		if (process_env_variable(&sh->env, *env) == -1)
			return (free_env_list(sh->env));
		(env)++;
	}
	increment_shlvl(sh->env);
	return (sh->env);
}

static int	process_env_variable(t_env **env, char *variable)
{
	char	**split;
	int		result;

	split = ft_split(variable, '=');
	if (!split || !split[0])
	{
		free_split(split);
		return (-1);
	}
	if (split[1] == NULL)
		result = add_env_variable(env, split[0], "");
	else
		result = add_env_variable(env, split[0], split[1]);
	free_split(split);
	return (result);
}

static void	increment_shlvl(t_env *env)
{
	char	*sh_lvl;

	sh_lvl = find_env_value(env, "SHLVL");
	sh_lvl = ft_itoa((ft_atoi(sh_lvl) + 1));
	update_env_value(env, "SHLVL", sh_lvl);
	ft_free((void **)&sh_lvl);
}
