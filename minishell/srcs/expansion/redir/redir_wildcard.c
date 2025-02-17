/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:23:39 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 16:08:43 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_wildcard_redir(t_redir *redir);

int	expand_redir_wildcards(t_redir *head)
{
	t_redir	*redir;

	redir = head;
	while (redir)
	{
		if (redir->type != T_HEREDOC
			&& has_wildcard_outside_quotes(redir->file))
		{
			if (!process_wildcard_redir(redir))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

static int	process_wildcard_redir(t_redir *redir)
{
	char	*result;

	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (0);
	if (!process_wildcard_expansion(redir->file, &result))
	{
		if (result)
			ft_free((void **)&result);
		return (0);
	}
	if (!handle_redir_word_expansion(redir, result))
	{
		if (result)
			ft_free((void **)&result);
		return (0);
	}
	if (result)
		ft_free((void **)&result);
	return (1);
}
