/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:39:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/09 15:49:39 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_env_word(t_shell *sh, t_redir *redir);

int	expand_redir_env(t_shell *sh, t_redir *head)
{
	t_redir	*redir;

	redir = head;
	while (redir)
	{
		if ((redir->type != T_HEREDOC) && redir->file
			&& has_env_outside_squotes(redir->file)
			&& ft_strlen(redir->file) > 1)
		{
			if (!expand_env_word(sh, redir))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

static int	expand_env_word(t_shell *sh, t_redir *redir)
{
	char	*result;

	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (0);
	if (!process_string_expansion(sh, redir->file, &result))
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

int	handle_redir_word_expansion(t_redir *redir, char *result)
{
	if (!result || !result[0])
	{
		print_error(NULL, redir->file, "ambiguous redirect");
		return (0);
	}
	if (!has_spaces_outside_quotes(result))
	{
		ft_free((void **)&redir->file);
		redir->file = ft_strdup(result);
		if (!redir->file)
			return (0);
		return (1);
	}
	else if (has_spaces_outside_quotes(result))
	{
		print_error(NULL, redir->file, "ambiguous redirect");
		return (0);
	}
	return (1);
}
