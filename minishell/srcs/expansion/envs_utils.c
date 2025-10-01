/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:08:35 by jrinta-           #+#    #+#             */
/*   Updated: 2025/10/01 14:00:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_spaces_outside_quotes(char *str)
{
	int	in_squote;
	int	in_dquote;
	int	i;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == ' ' && !in_squote && !in_dquote)
			return (1);
		i++;
	}
	return (0);
}

int	has_env_outside_squotes(char *str)
{
	int	in_squote;
	int	in_dquote;
	int	i;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '$' && !in_squote)
			return (1);
		i++;
	}
	return (0);
}

char	*find_env_value_malloced(t_env *env, char *key)
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
			ft_free((void **)&key);
			if (temp->value)
				return (ft_strdup(temp->value));
			return (ft_strdup(""));
		}
		temp = temp->next;
	}
	ft_free((void **)&key);
	return (ft_strdup(""));
}

char	*exit_status(t_shell *sh)
{
	char	*value;

	value = ft_itoa(sh->exit_status);
	if (!value)
		return (NULL);
	return (value);
}

//	Joins two strings and on success frees everything but the result.
char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		return (NULL);
	ft_free((void **)&s1);
	ft_free((void **)&s2);
	return (result);
}
