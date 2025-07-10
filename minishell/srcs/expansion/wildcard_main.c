/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:05:47 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/08 23:43:33 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_matches(DIR *dir_ptr, char **result, char *wildcard);
static int	is_match(char *s, char *p);
static void	init_pattern_and_indexes(t_pattern *pat, char *str, t_index *i);

int	process_wildcard_expansion(char *wildcard, char **result)
{
	DIR		*dir_ptr;

	dir_ptr = opendir(".");
	if (!dir_ptr)
	{
		ft_putstr_fd("Can't open the directory.\n", STDERR_FILENO);
		return (0);
	}
	if (!find_matches(dir_ptr, result, wildcard))
		return (0);
	if (closedir(dir_ptr) == -1)
		ft_putstr_fd("Failure closing the dir\n", STDERR_FILENO);
	return (1);
}

static int	find_matches(DIR *dir_ptr, char **result, char *wildcard)
{
	struct dirent	*read_dir;

	while (42)
	{
		read_dir = readdir(dir_ptr);
		if (!read_dir)
			break ;
		if (read_dir->d_name[0] == '.')
			continue ;
		if (is_match(read_dir->d_name, wildcard))
		{
			*result = ft_strjoin_quotes(*result, read_dir->d_name);
			if (!*result)
				return (0);
		}
	}
	if (!*result)
		*result = ft_strdup(wildcard);
	if (!*result)
		return (0);
	return (1);
}

static int	is_match(char *s, char *p)
{
	t_pattern	pat;
	t_index		i;

	init_pattern_and_indexes(&pat, p, &i);
	while (s[i.s_i])
		if (!wildcard_logic(&pat, s, &i))
			return (0);
	if (!check_end_pattern(&pat))
		return (0);
	return (pat.current == '\0');
}

static void	init_pattern_and_indexes(t_pattern *pat, char *str, t_index *i)
{
	pat->str = str;
	pat->i = 0;
	pat->in_dquote = 0;
	pat->in_squote = 0;
	pat->current = str[0];
	if (pat->current == '\'')
		pat->in_squote = !pat->in_squote;
	else if (pat->current == '"')
		pat->in_dquote = !pat->in_dquote;
	i->s_i = 0;
	i->star_pat_i = -1;
	i->star_s_i = -1;
}

int	has_wildcard_outside_quotes(char *str)
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
		else if (str[i] == '*' && !in_squote && !in_dquote)
			return (1);
		i++;
	}
	return (0);
}
