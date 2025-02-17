/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:03:06 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/04 16:04:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*find_env_var(char *var, char **envp)
{
	int		i;
	char	*value;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			value = ft_strchr(envp[i], '=') + 1;
			return (value);
		}
		i++;
	}
	return (NULL);
}

static	char	**get_paths_from_env(char **envp)
{
	char	*path;
	char	**paths;

	path = find_env_var("PATH", envp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

static	char	*join_path_cmd(char *path, char *cmd)
{
	char	*cmd_path_tmp;
	char	*cmd_path;

	cmd_path_tmp = ft_strjoin(path, "/");
	if (!cmd_path_tmp)
		return (NULL);
	cmd_path = ft_strjoin(cmd_path_tmp, cmd);
	ft_free((void **)&cmd_path_tmp);
	return (cmd_path);
}

static	char	*search_cmd_in_paths(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = join_path_cmd(paths[i], cmd);
		if (!cmd_path)
		{
			return (NULL);
		}
		if (access(cmd_path, F_OK) == 0)
		{
			return (cmd_path);
		}
		ft_free((void **)&cmd_path);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;

	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	cmd_path = search_cmd_in_paths(cmd, paths);
	free_split(paths);
	return (cmd_path);
}
