/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:25:18 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/12 17:27:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_args(t_shell *sh, t_args *args)
{
	if (!expand_env(sh, args))
		return (0);
	if (!expand_wildcards(args))
		return (0);
	if (!strip_quotes_cmd(args))
		return (0);
	return (1);
}

static int	expand_redirs(t_shell *sh, t_redir *redir)
{
	if (!expand_redir_env(sh, redir))
		return (0);
	if (!expand_redir_wildcards(redir))
		return (0);
	if (!strip_quotes_redir(redir))
		return (0);
	return (1);
}

static void	debug_redirects(t_redir *redir, int depth)
{
	int	i;

	depth++;
	while (redir)
	{
		i = -1;
		while (++i < depth)
			printf("  ");
		if (redir->hd_delimit)
			printf("Heredoc Delimiter: '%s'\n", redir->hd_delimit);
		else
			printf("Redirection: Type '%d', File: '%s'\n", redir->type,
				redir->file);
		redir = redir->next;
	}
}

void	debug_cmd_node(t_shell *sh, t_node *node, int depth)
{
	t_args	*arg;
	t_redir	*redir;

	arg = node->data.command.args;
	redir = node->data.command.redirects;
	printf("Command: ");
	if (!expand_args(sh, arg))
	{
		free_ast(node);
		return ;
	}
	while (arg)
	{
		printf("%s ", arg->value);
		arg = arg->next;
	}
	printf("\n");
	if (!expand_redirs(sh, redir))
	{
		free_ast(node);
		return ;
	}
	if (redir)
		debug_redirects(redir, depth);
}
