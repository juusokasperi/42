/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:00:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/03 00:33:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		append_arg_to_cmd(t_args **args, t_token **tokens);
static int		parse_and_append_redir(t_redir **redir, t_token **tokens);
static t_node	*parse_subshell(t_token **tokens);

t_node	*parse_redir_or_cmd(t_token **tokens)
{
	t_node	*cmd;
	t_redir	*redir;

	redir = NULL;
	while (is_redir_token((*tokens)->type))
		if (!parse_and_append_redir(&redir, tokens))
			return (NULL);
	if ((*tokens)->type == T_PAREN_L)
		cmd = parse_subshell(tokens);
	else
		cmd = parse_simple_cmd(tokens);
	if (!cmd)
		return (NULL);
	while ((*tokens)->type == T_WORD || is_redir_token((*tokens)->type))
	{
		if ((*tokens)->type == T_WORD)
		{
			if (!append_arg_to_cmd(&cmd->data.command.args, tokens))
				return (free_ast(cmd));
		}
		else if (!parse_and_append_redir(&redir, tokens))
			return (free_ast(cmd));
	}
	cmd->data.command.redirects = redir;
	return (cmd);
}

static int	parse_and_append_redir(t_redir **redir, t_token **tokens)
{
	t_token_type	type;

	type = (*tokens)->type;
	consume_token(tokens);
	if (!rediradd_back(redir, type, (*tokens)->value))
		return (0);
	consume_token(tokens);
	return (1);
}

static t_node	*parse_subshell(t_token **tokens)
{
	t_node	*cmd;

	consume_token(tokens);
	cmd = parse_expressions(tokens);
	if (!cmd || (*tokens)->type != T_PAREN_R)
		return (free_ast(cmd));
	consume_token(tokens);
	cmd = create_subsh_node(cmd);
	if (!cmd)
		return (NULL);
	return (cmd);
}

static int	append_arg_to_cmd(t_args **args, t_token **tokens)
{
	if (argadd_back(args,
			arglst_new((*tokens)->value)))
		return (0);
	consume_token(tokens);
	return (1);
}
