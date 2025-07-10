/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:58:50 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 15:47:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_variable(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

//add to list sh->env
int	add_env_variable(t_env **env, char *key, char *value)
{
	if (envadd_back(env, envlst_new(key, value)))
		return (-1);
	return (0);
}

int	update_env_value(t_env *env, char *key, char *value)
{
	t_env	*temp;
	size_t	key_len;

	temp = env;
	key_len = ft_strlen(key);
	while (temp)
	{
		if (ft_strncmp(key, temp->key, key_len) == 0
			&& ft_strlen(temp->key) == key_len)
		{
			ft_free((void **)&(temp->value));
			temp->value = ft_strdup(value);
			if (!temp->value)
				return (-1);
			return (0);
		}
		temp = temp->next;
	}
	return (envadd_back(&env, envlst_new(key, value)));
}

char	*find_env_value(t_env *env, char *key)
{
	t_env	*temp;
	size_t	key_len;

	temp = env;
	key_len = ft_strlen(key);
	while (temp)
	{
		if (ft_strncmp(key, temp->key, key_len) == 0
			&& ft_strlen(temp->key) == key_len)
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}
