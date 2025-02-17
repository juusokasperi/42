/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_cmd_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:29:36 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/05 23:44:35 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*handle_append_truncate_out(t_redir *new_redir, char *str);
static t_redir	*handle_heredoc_ast(t_redir	*new_redir, char *str);

t_redir	*redirlst_new(t_token_type type, char *str)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->hd_preprocessed_fd = -1;
	if (type == T_TRUNCATE || type == T_IN || type == T_APPEND)
		new_redir = handle_append_truncate_out(new_redir, str);
	else
		new_redir = handle_heredoc_ast(new_redir, str);
	if (!new_redir)
		return (NULL);
	new_redir->next = NULL;
	return (new_redir);
}

static t_redir	*handle_append_truncate_out(t_redir *new_redir, char *str)
{
	new_redir->file = ft_strdup(str);
	if (!new_redir->file)
	{
		ft_free((void **)&new_redir);
		return (NULL);
	}
	return (new_redir);
}

static t_redir	*handle_heredoc_ast(t_redir	*new_redir, char *str)
{
	new_redir->hd_delimit = ft_strdup(str);
	if (!new_redir->hd_delimit)
	{
		ft_free((void **)&new_redir);
		return (NULL);
	}
	new_redir->hd_content = NULL;
	return (new_redir);
}

int	rediradd_back(t_redir **redir, t_token_type type, char *str)
{
	t_redir	*new_redir;
	t_redir	*temp;

	new_redir = redirlst_new(type, str);
	if (!new_redir)
		return (0);
	if (!*redir)
		*redir = new_redir;
	else
	{
		temp = *redir;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
	return (1);
}
