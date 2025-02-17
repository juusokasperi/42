/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:37:39 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/09 18:26:19 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *cmd_path)
{
	DIR	*dir;

	errno = 0;
	dir = opendir(cmd_path);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	if (errno != ENOTDIR)
		return (1);
	return (0);
}

void	handle_cmd_not_found(t_args *args)
{
	if (!args)
		return ;
	if (ft_strchr(args->value, '/') == NULL)
		print_error(NULL, args->value, "command not found");
	else if (access(args->value, F_OK) == -1)
		print_error(NULL, args->value, "No such file or directory");
	else
		print_error(NULL, args->value, "command not found");
	free_args(args);
	exit(127);
}

void	handle_permission_denied(char *cmd_path, t_args *args)
{
	print_error(NULL, args->value, "Permission denied");
	ft_free((void **)&cmd_path);
	free_args(args);
	exit(126);
}

void	handle_is_directory(char *cmd_path, t_args *args)
{
	print_error(NULL, args->value, "Is a directory");
	ft_free((void **)&cmd_path);
	free_args(args);
	exit(126);
}

void	handle_execve_error(char *cmd_path, t_args *args)
{
	print_error(NULL, args->value, strerror(errno));
	ft_free((void **)&cmd_path);
	free_args(args);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}
