/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:32:29 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/09 18:16:22 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target(t_shell *sh, t_args *args)
{
	char	*target;

	if (!args->next)
	{
		target = find_env_value(sh->env, "HOME");
		if (!target || !*target)
		{
			print_error("cd", NULL, "HOME not set");
			return (NULL);
		}
	}
	else
		target = args->next->value;
	return (target);
}

static int	change_directory(char *target, char old_pwd[PATH_MAX])
{
	if (!getcwd(old_pwd, sizeof(char) * PATH_MAX))
	{
		print_error("cd", NULL, "getcwd failed");
		return (EXIT_FAILURE);
	}
	if (chdir(target) != 0)
	{
		print_error("cd", target, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	update_pwd_env(t_shell *sh, char old_pwd[PATH_MAX])
{
	char	*new_pwd;

	update_env_value(sh->env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_error("cd", NULL, "getcwd failed");
		return (EXIT_FAILURE);
	}
	update_env_value(sh->env, "PWD", new_pwd);
	free(new_pwd);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_shell *sh, t_args *args)
{
	char	*target;
	char	old_pwd[PATH_MAX];

	if (args && args->next && args->next->next)
	{
		print_error("cd", NULL, "too many arguments");
		return (EXIT_FAILURE);
	}
	target = get_target(sh, args);
	if (!target)
		return (EXIT_FAILURE);
	if (change_directory(target, old_pwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (update_pwd_env(sh, old_pwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
