/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:10:16 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/09 14:54:08 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		print_error("pwd", NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	ft_free((void **)&cwd);
	return (EXIT_SUCCESS);
}
