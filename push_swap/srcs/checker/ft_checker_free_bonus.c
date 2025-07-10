/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_free_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 14:20:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/04 14:46:59 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	ft_error_free(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_a && *stack_a)
		ft_stackclear(stack_a, NULL);
	if (stack_b && *stack_b)
		ft_stackclear(stack_b, NULL);
	ft_putstr_fd("Error\n", 2);
	exit (1);
}

void	ft_error_free_line(t_stack **stack_a, t_stack **stack_b, char *line)
{
	free(line);
	ft_error_free(stack_a, stack_b);
}
