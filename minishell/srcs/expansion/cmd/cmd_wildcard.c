/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:23:04 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 16:07:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_wildcard_cmd(t_args *arg);

int	expand_wildcards(t_args *head)
{
	t_args	*arg;

	arg = head;
	while (arg)
	{
		if (has_wildcard_outside_quotes(arg->value))
		{
			if (!process_wildcard_cmd(arg))
				return (0);
		}
		arg = arg->next;
	}
	return (1);
}

static int	process_wildcard_cmd(t_args *arg)
{
	char	*result;

	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (0);
	if (!process_wildcard_expansion(arg->value, &result))
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
