/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:58:21 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 16:07:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_env_word(t_shell *sh, t_args *arg);
static int	insert_into_list(t_args *arg, char *result);

int	expand_env(t_shell *sh, t_args *head)
{
	t_args	*arg;

	arg = head;
	while (arg)
	{
		if (has_env_outside_squotes(arg->value) && ft_strlen(arg->value) > 1)
		{
			if (!expand_env_word(sh, arg))
				return (0);
		}
		arg = arg->next;
	}
	return (1);
}

static int	expand_env_word(t_shell *sh, t_args *arg)
{
	char	*result;

	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (0);
	if (!process_string_expansion(sh, arg->value, &result))
	{
		if (result)
			ft_free((void **)&result);
		return (0);
	}
	if (!handle_word_expansion(arg, result))
	{
		if (result)
			ft_free((void **)&result);
		return (0);
	}
	if (result)
		ft_free((void **)&result);
	return (1);
}

int	handle_word_expansion(t_args *arg, char *result)
{
	if (has_spaces_outside_quotes(result))
	{
		if (!insert_into_list(arg, result))
			return (0);
	}
	else
	{
		if (!update_arg_value(arg, result))
			return (0);
	}
	return (1);
}

static int	insert_into_list(t_args *arg, char *result)
{
	char	**split;

	split = split_outside_quotes(result);
	if (!split)
		return (0);
	if (!split_and_insert(arg, split))
	{
		free_split(split);
		return (0);
	}
	free_split(split);
	return (1);
}

int	update_arg_value(t_args *arg, char *value)
{
	ft_free((void **)&arg->value);
	arg->value = ft_strdup(value);
	if (!arg->value)
		return (0);
	return (1);
}
