/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:17:37 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/09 18:16:41 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd_path(char *cmd, char **envp)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (!envp)
		return (NULL);
	return (find_cmd_path(cmd, envp));
}

void	execute_external_cmd(t_shell *sh, t_node *node)
{
	char	*cmd_path;
	char	**envp;
	char	**cmd;

	handle_array_conversion(sh, node, &envp, &cmd);
	if (!envp || !cmd)
	{
		print_error(NULL, "Malloc",
			"Failed to convert lists to arrays for execve");
		exit(1);
	}
	cmd_path = get_cmd_path(node->data.command.args->value, envp);
	if (cmd_path == NULL)
		handle_cmd_not_found(node->data.command.args);
	else if (access(cmd_path, F_OK) != 0)
		handle_cmd_not_found(node->data.command.args);
	else if (is_dir(cmd_path))
		handle_is_directory(cmd_path, node->data.command.args);
	else if (access(cmd_path, X_OK) != 0)
		handle_permission_denied(cmd_path, node->data.command.args);
	else if (execve(cmd_path, cmd, envp) == -1)
		handle_execve_error(cmd_path, node->data.command.args);
	ft_free((void **)&cmd_path);
	free_split(envp);
	free_split(cmd);
}
