/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:41:51 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/15 13:49:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_type	get_builtin_type(char *cmd)
{
	if (!cmd)
		return (NOT_BUILTIN);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (BUILTIN_NO_FORK);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "pwd"))
		return (BUILTIN_FORK);
	return (NOT_BUILTIN);
}

int	execute_builtin(t_shell *sh, t_node *node)
{
	if (!ft_strcmp(node->data.command.args->value, "echo"))
		return (ft_echo(node->data.command.args));
	else if (!ft_strcmp(node->data.command.args->value, "cd"))
		return (ft_cd(sh, node->data.command.args));
	else if (!ft_strcmp(node->data.command.args->value, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(node->data.command.args->value, "export"))
		return (ft_export(sh, node->data.command.args));
	else if (!ft_strcmp(node->data.command.args->value, "unset"))
		return (ft_unset(sh, node->data.command.args));
	else if (!ft_strcmp(node->data.command.args->value, "env"))
		return (ft_env(sh));
	else if (!ft_strcmp(node->data.command.args->value, "exit"))
		return (ft_exit(sh, node->data.command.args));
	return (EXIT_SUCCESS);
}
