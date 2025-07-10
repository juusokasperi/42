/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_envs_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:00:39 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/02 23:52:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char *str, t_split *s);
static void	update_quotes(char c, t_split *s);
static int	count_words(const char *str);

char	**split_outside_quotes(char *str)
{
	char	**words;
	t_split	s;

	words = ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!words)
		return (NULL);
	s = (t_split){0};
	while (str[s.i])
	{
		skip_spaces(str, &s);
		if (!str[s.i])
			break ;
		while (str[s.j] && !(str[s.j] == ' ' && !s.in_dquote && !s.in_squote))
			update_quotes(str[s.j++], &s);
		words[s.count] = ft_substr(str, s.i, s.j - s.i);
		if (!words[s.count])
		{
			free_split(words);
			return (NULL);
		}
		s.count++;
		s.i = s.j;
	}
	words[s.count] = NULL;
	return (words);
}

int	split_and_insert(t_args *arg, char **split)
{
	t_args	*new_arg;
	t_args	*last_extended;
	int		i;

	if (!update_arg_value(arg, split[0]))
		return (0);
	new_arg = NULL;
	i = 1;
	while (split[i])
	{
		if (argadd_back(&new_arg, arglst_new(split[i])))
		{
			free_args(new_arg);
			return (0);
		}
		i++;
	}
	last_extended = new_arg;
	while (last_extended->next)
		last_extended = last_extended->next;
	last_extended->next = arg->next;
	arg->next = new_arg;
	return (1);
}

static void	skip_spaces(char *str, t_split *s)
{
	while (str[s->i] == ' ' && !s->in_dquote && !s->in_dquote)
		s->i++;
	s->j = s->i;
}

static void	update_quotes(char c, t_split *s)
{
	if (c == '\'' && !s->in_dquote)
		s->in_squote = !s->in_squote;
	else if (c == '\"' && !s->in_squote)
		s->in_dquote = !s->in_dquote;
}

static int	count_words(const char *str)
{
	int	count;
	int	in_squote;
	int	in_dquote;

	count = 0;
	in_squote = 0;
	in_dquote = 0;
	while (*str)
	{
		while (*str == ' ' && !in_squote && !in_dquote)
			str++;
		if (*str)
			count++;
		while (*str)
		{
			if (*str == '\'' && !in_dquote)
				in_squote = !in_squote;
			else if (*str == '\"' && !in_squote)
				in_dquote = !in_dquote;
			else if (*str == ' ' && !in_squote && !in_dquote)
				break ;
			str++;
		}
	}
	return (count);
}
