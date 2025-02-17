/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:31:46 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/05 20:58:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate_env_list_len(t_env *env);
static char	*create_env_array_item(char *key, char *value);
static char	**create_env_array(char **envp, t_env *env);

char	**convert_env_list_to_array(t_env *env)
{
	char	**envp;
	int		len;

	len = calculate_env_list_len(env);
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	envp = create_env_array(envp, env);
	if (!envp)
		return (NULL);
	return (envp);
}

static int	calculate_env_list_len(t_env *env)
{
	int		len;
	t_env	*temp;

	temp = env;
	len = 0;
	while (temp)
	{
		if (temp->value)
			len++;
		temp = temp->next;
	}
	return (len);
}

static char	*create_env_array_item(char *key, char *value)
{
	char	*envp;
	char	*envp_temp;

	envp_temp = ft_strjoin(key, "=");
	if (!envp_temp)
		return (NULL);
	envp = ft_strjoin(envp_temp, value);
	ft_free((void **)&envp_temp);
	if (!envp)
		return (NULL);
	return (envp);
}

static char	**create_env_array(char **envp, t_env *env)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = env;
	while (temp)
	{
		if (temp->value)
		{
			envp[i] = create_env_array_item(temp->key, temp->value);
			if (!envp[i])
			{
				while (--i >= 0)
					ft_free((void **)&envp[i]);
				return (NULL);
			}
			i++;
		}
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}
