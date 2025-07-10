/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:07:48 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/27 19:30:30 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_calculate(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;
	int		size_a;
	int		size_b;

	tmp_a = *stack_a;
	tmp_b = *stack_b;
	size_a = ft_stacksize(tmp_a);
	size_b = ft_stacksize(tmp_b);
	while (tmp_b)
	{
		tmp_b->cost_b = tmp_b->pos;
		if (tmp_b->pos > size_b / 2)
			tmp_b->cost_b = (size_b - tmp_b->pos) * -1;
		tmp_b->cost_a = tmp_b->target;
		if (tmp_b->target > size_a / 2)
			tmp_b->cost_a = (size_a - tmp_b->target) * -1;
		tmp_b = tmp_b->next;
	}
}

void	ft_execute(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	int		cheap;
	int		cost_a;
	int		cost_b;

	tmp = *stack_b;
	cheap = ft_abs(tmp->cost_b) + ft_abs(tmp->cost_a);
	cost_a = tmp->cost_a;
	cost_b = tmp->cost_b;
	while (tmp)
	{
		if (ft_abs(tmp->cost_a) + ft_abs(tmp->cost_b) < cheap)
		{
			cheap = ft_abs(tmp->cost_b) + ft_abs(tmp->cost_a);
			cost_a = tmp->cost_a;
			cost_b = tmp->cost_b;
		}
		tmp = tmp->next;
	}
	ft_move(stack_a, stack_b, cost_a, cost_b);
}
