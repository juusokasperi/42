/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_reverse_rotate_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 00:13:08 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/04 14:49:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	ft_reverse_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*new_last;

	if (!*stack || !(*stack)->next)
		return ;
	new_last = *stack;
	while (new_last->next->next)
		new_last = new_last->next;
	last = new_last->next;
	new_last->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	ft_rra(t_stack **stack_a)
{
	ft_reverse_rotate(stack_a);
}

void	ft_rrb(t_stack **stack_b)
{
	ft_reverse_rotate(stack_b);
}

void	ft_rrr(t_stack **stack_a, t_stack **stack_b)
{
	ft_reverse_rotate(stack_a);
	ft_reverse_rotate(stack_b);
}
