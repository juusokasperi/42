/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:10:34 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/03 15:45:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	next_char(t_pattern *pat);
static void	backtrack_to_last_wildcard(t_pattern *pat, t_index *i);

int	wildcard_logic(t_pattern *pat, char *s, t_index *i)
{
	if ((pat->current == '\'' && !pat->in_dquote)
		|| (pat->current == '"' && !pat->in_squote))
		next_char(pat);
	else if (pat->current == s[i->s_i] && !pat->in_squote && !pat->in_dquote)
	{
		(i->s_i)++;
		next_char(pat);
	}
	else if (pat->current == '*' && !pat->in_squote && !pat->in_dquote)
	{
		i->star_pat_i = pat->i;
		i->star_s_i = i->s_i;
		next_char(pat);
	}
	else if ((pat->in_squote || pat->in_dquote) && pat->current == s[i->s_i])
	{
		(i->s_i)++;
		next_char(pat);
	}
	else if (i->star_pat_i != -1)
		backtrack_to_last_wildcard(pat, i);
	else
		return (0);
	return (1);
}

static void	next_char(t_pattern *pat)
{
	if (pat->str[pat->i] == '\0')
	{
		pat->current = '\0';
		return ;
	}
	pat->i++;
	pat->current = pat->str[pat->i];
	if (pat->current == '\'' && !pat->in_dquote)
	{
		pat->in_squote = !pat->in_squote;
		pat->i++;
		pat->current = pat->str[pat->i];
	}
	else if (pat->current == '"' && !pat->in_squote)
	{
		pat->in_dquote = !pat->in_dquote;
		pat->i++;
		pat->current = pat->str[pat->i];
	}
}

static void	backtrack_to_last_wildcard(t_pattern *pat, t_index *i)
{
	pat->i = i->star_pat_i;
	pat->in_dquote = 0;
	pat->in_squote = 0;
	pat->current = pat->str[pat->i];
	next_char(pat);
	i->s_i = ++(i->star_s_i);
}

int	check_end_pattern(t_pattern *pat)
{
	while (pat->current)
	{
		if ((pat->current == '\'' && !pat->in_dquote)
			|| (pat->current == '"' && !pat->in_squote))
			next_char(pat);
		else if (pat->current == '*' && !pat->in_dquote && !pat->in_squote)
			next_char(pat);
		else
			return (0);
	}
	return (1);
}
