/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 23:56:01 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 16:04:49 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_quotes(char **result, char *file, t_split *in);
static int	process_text(t_shell *sh, char *file, char **result, t_split *in);
static char	*process_env_var(t_shell *sh, char *file, int *i, int *j);
static char	*process_non_env(char *file, t_split *in);

int	process_string_expansion(t_shell *sh, char *file, char **result)
{
	t_split	in;

	in = (t_split){0};
	while (file[in.i])
	{
		if ((file[in.i] == '\'' && !in.in_dquote)
			|| (file[in.i] == '"' && !in.in_squote))
		{
			if (!process_quotes(result, file, &in))
				return (0);
			continue ;
		}
		if (!process_text(sh, file, result, &in))
			return (0);
		in.i = in.j;
	}
	return (1);
}

static int	process_quotes(char **result, char *file, t_split *in)
{
	char	*substr;
	char	*temp;

	substr = ft_substr(file, in->i, 1);
	if (!substr)
		return (0);
	temp = join_and_free(*result, substr);
	if (!temp)
	{
		ft_free((void **)result);
		ft_free((void **)&substr);
		return (0);
	}
	*result = temp;
	if (file[in->i] == '\'')
		in->in_squote = !in->in_squote;
	else
		in->in_dquote = !in->in_dquote;
	(in->i)++;
	return (1);
}

static int	process_text(t_shell *sh, char *file, char **result, t_split *in)
{
	char	*value;

	if (file[in->i] == '$' && !in->in_squote)
		value = process_env_var(sh, file, &(in->i), &(in->j));
	else
		value = process_non_env(file, in);
	if (!value)
		return (0);
	*result = join_and_free(*result, value);
	if (!*result)
	{
		ft_free((void **)&value);
		return (0);
	}
	return (1);
}

static char	*process_env_var(t_shell *sh, char *file, int *i, int *j)
{
	char	*value;

	(*i)++;
	*j = *i;
	if (!file[*i] || (!ft_isalnum(file[*i])
			&& file[*i] != '?' && file[*i] != '_'))
		return (ft_strdup("$"));
	if (file[*j] == '?')
	{
		(*j)++;
		return (exit_status(sh));
	}
	while (file[*j]
		&& (ft_isalnum(file[*j]) || file[*j] == '_'))
		(*j)++;
	value = ft_substr(file, *i, *j - *i);
	if (!value)
		return (NULL);
	value = find_env_value_malloced(sh->env, value);
	if (!value)
		return (NULL);
	return (value);
}

static char	*process_non_env(char *file, t_split *in)
{
	char	*value;

	in->j = in->i;
	while (file[in->j] && !(file[in->j] == '$' && !in->in_squote)
		&& !(file[in->j] == '\'' && !in->in_dquote)
		&& !(file[in->j] == '"' && !in->in_squote))
		in->j++;
	value = ft_substr(file, in->i, in->j - in->i);
	if (!value)
		return (NULL);
	return (value);
}
