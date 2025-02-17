/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:36:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/09 23:57:34 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_values(t_args **args);

int	handle_redir_expansions(t_shell *sh, t_node *node)
{
	if (!expand_redir_env(sh, node->data.command.redirects)
		|| !expand_redir_wildcards(node->data.command.redirects)
		|| !strip_quotes_redir(node->data.command.redirects))
		return (-1);
	return (0);
}

int	handle_expansions(t_shell *sh, t_node *node)
{
	if (!expand_env(sh, node->data.command.args)
		|| !expand_wildcards(node->data.command.args))
		return (-1);
	if (!has_values(&node->data.command.args))
		return (0);
	if (!strip_quotes_cmd(node->data.command.args))
		return (-1);
	return (0);
}

// Check for empty strings in command args.
// F.ex. $VAR is uninitialized and the input is $VAR echo test. After expansion,
// the first argument is just a "\0" -> needs to be removed. On the other hand,
// if input is "$VAR" echo test, the first argument is treated as a command.
// echo test $EMPTY world should print out 'test world', not 'test  world'
static int	has_values(t_args **args)
{
	t_args	*current;
	t_args	*prev;
	t_args	*next;

	current = *args;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->value && current->value[0] == '\0')
		{
			if (prev)
				prev->next = next;
			else
				*args = next;
			ft_free((void **)&current->value);
			ft_free((void **)&current);
		}
		else
		{
			prev = current;
			current = next;
		}
	}
	return (*args != NULL);
}
