/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:56:40 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/15 14:39:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_args(t_shell *sh, t_args *args);
static char	**parse_export_args(char *arg);
static char	**allocate_and_set_key(char *arg, int *i);
static int	ft_export_no_args(t_shell *sh);

int	ft_export(t_shell *sh, t_args *args)
{
	t_args	*tmp;
	bool	err;

	if (!args->next)
		return (ft_export_no_args(sh));
	tmp = args->next;
	err = false;
	while (tmp)
	{
		if (ft_export_args(sh, tmp))
			err = true;
		tmp = tmp->next;
	}
	if (err)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_export_no_args(t_shell *sh)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (env->value)
		{
			if (printf("declare -x %s=\"%s\"\n", env->key, env->value) == -1)
				return (EXIT_FAILURE);
		}
		else
		{
			if (printf("declare -x %s\n", env->key) == -1)
				return (EXIT_FAILURE);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

static int	ft_export_args(t_shell *sh, t_args *args)
{
	char	**tmp;
	char	*key;
	char	*value;
	t_env	*env;
	int		result;

	result = -1;
	tmp = parse_export_args(args->value);
	if (!tmp)
		return (EXIT_FAILURE);
	key = tmp[0];
	if (tmp[1])
		value = tmp[1];
	else
		value = NULL;
	env = find_env_variable(sh->env, key);
	if (env && value)
		result = update_env_value(env, key, value);
	else if (!env)
		result = add_env_variable(&sh->env, key, value);
	free_split(tmp);
	return (result);
}

static char	**parse_export_args(char *arg)
{
	char	**tmp;
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	if (!valid_identifier(arg, "export"))
		return (NULL);
	tmp = allocate_and_set_key(arg, &i);
	if (!tmp)
		return (NULL);
	if (arg[i] == '=')
	{
		if (!(arg[i + 1]))
			tmp[1] = ft_strdup("");
		else
			tmp[1] = ft_strdup(arg + i + 1);
		if (!tmp[1])
		{
			free_split(tmp);
			return (NULL);
		}
	}
	return (tmp);
}

static char	**allocate_and_set_key(char *arg, int *i)
{
	char	**tmp;

	while (arg[*i] && arg[*i] != '=')
		(*i)++;
	if (arg[*i] != '=')
		tmp = ft_calloc(2, sizeof(char *));
	else
		tmp = ft_calloc(3, sizeof(char *));
	if (!tmp)
		return (NULL);
	tmp[0] = ft_substr(arg, 0, *i);
	if (!tmp[0])
	{
		free_split(tmp);
		return (NULL);
	}
	return (tmp);
}
