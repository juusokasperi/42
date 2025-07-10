/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_rotate_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:59:44 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/04 14:49:19 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	ft_rotate(t_stack **stack)
{
	t_stack	*tmp;
	t_stack	*end;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = NULL;
	end = *stack;
	while (end->next)
		end = end->next;
	end->next = tmp;
}

void	ft_ra(t_stack **stack_a)
{
	ft_rotate(stack_a);
}

void	ft_rb(t_stack **stack_b)
{
	ft_rotate(stack_b);
}

void	ft_rr(t_stack **stack_a, t_stack **stack_b)
{
	ft_rotate(stack_a);
	ft_rotate(stack_b);
}
