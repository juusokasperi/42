/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:56:33 by phuocngu          #+#    #+#             */
/*   Updated: 2025/02/10 23:28:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_logical(t_shell *sh, t_node *node, int input_fd, int output_fd)
{
	int	left_status;

	left_status = execute_node(sh, node->data.binary.left, input_fd, output_fd);
	if (ft_strcmp(node->data.binary.operator, "&&") == 0)
	{
		if (left_status == 0 && sh->exit == 0)
			return (execute_node(sh, node->data.binary.right, input_fd,
					output_fd));
		else
			return (left_status);
	}
	else if (ft_strcmp(node->data.binary.operator, "||") == 0)
	{
		if (left_status != 0)
			return (execute_node(sh, node->data.binary.right, input_fd,
					output_fd));
		else
			return (left_status);
	}
	print_error(NULL, NULL, "Unknown logical operator.");
	return (left_status);
}
