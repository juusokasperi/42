/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:12:49 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 16:06:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	strip_quotes(char **str);

int	strip_quotes_cmd(t_args *head)
{
	t_args	*arg;

	arg = head;
	while (arg)
	{
		if (!strip_quotes(&(arg->value)))
			return (0);
		arg = arg->next;
	}
	return (1);
}

int	strip_quotes_redir(t_redir *head)
{
	t_redir	*redir;

	redir = head;
	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			if (!strip_quotes(&(redir->hd_delimit)))
				return (0);
		}
		else
		{
			if (!strip_quotes(&(redir->file)))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

static void	remove_quotes(char *str, int *i, int *j, char **result)
{
	char	quote;
	char	*tmp;
	char	*joined_str;

	quote = str[*i];
	(*i)++;
	*j = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	tmp = ft_substr(str, *j, *i - *j);
	if (!tmp)
	{
		ft_free((void **)result);
		return ;
	}
	joined_str = join_and_free(*result, tmp);
	if (!joined_str)
	{
		ft_free((void **)&tmp);
		ft_free((void **)&result);
		return ;
	}
	*result = joined_str;
	if (str[*i])
		(*i)++;
}

static void	copy_till_quote_or_end(char *str, int *i, int *j, char **result)
{
	char	*tmp;
	char	*joined_str;

	*j = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	tmp = ft_substr(str, *j, *i - *j);
	if (!tmp)
	{
		ft_free((void **)result);
		return ;
	}
	joined_str = join_and_free(*result, tmp);
	if (!joined_str)
	{
		ft_free((void **)&tmp);
		ft_free((void **)&result);
		return ;
	}
	*result = joined_str;
}

static int	strip_quotes(char **str)
{
	int		i;
	int		j;
	char	*result;

	if (!*str)
		return (0);
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
			remove_quotes(*str, &i, &j, &result);
		else
			copy_till_quote_or_end(*str, &i, &j, &result);
		if (!result)
			return (0);
	}
	if (*str)
		ft_free((void **)str);
	*str = result;
	return (1);
}
