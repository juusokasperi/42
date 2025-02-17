/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:50:55 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 15:48:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_last(t_env *lst);

t_env	*free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		ft_free((void **)&env->key);
		if (env->value)
			ft_free((void **)&env->value);
		ft_free((void **)&env);
		env = temp;
	}
	return (NULL);
}

t_env	*envlst_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->key = ft_strdup(key);
	new->next = NULL;
	return (new);
}

int	envadd_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!new)
		return (1);
	last = env_last(*env);
	if (!last)
		*env = new;
	else
		last->next = new;
	return (0);
}

static t_env	*env_last(t_env *env)
{
	t_env	*ptr;

	if (!env)
		return (NULL);
	ptr = env;
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	return (ptr);
}
