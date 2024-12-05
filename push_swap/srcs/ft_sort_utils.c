/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:44:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/05 13:41:28 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_five_helper(t_stack **stack_a)
{
	if ((*stack_a)->rank > 1)
	{
		if ((*stack_a)->next->rank <= 1)
			ft_sa(stack_a);
		else if (ft_stacklast(*stack_a)->rank <= 1)
			ft_rra(stack_a);
		else if ((*stack_a)->next->next->rank <= 1)
		{
			ft_ra(stack_a);
			ft_ra(stack_a);
		}
		else
		{
			ft_rra(stack_a);
			ft_rra(stack_a);
		}
	}
}

void	ft_biggest_three(t_stack **stack_a, t_stack **stack_b,
	int stack_size, int values_pushed)
{
	int	stack_divider;

	stack_divider = stack_size / 2;
	while (stack_size > 6 && values_pushed < stack_divider)
	{
		if ((*stack_a)->rank <= stack_divider)
		{
			ft_pb(stack_a, stack_b);
			values_pushed++;
			stack_size--;
		}
		else
			ft_ra(stack_a);
	}
	while (stack_size > 3)
	{
		if ((*stack_a)->rank < ft_find_highest(*stack_a) - 2)
		{
			ft_pb(stack_a, stack_b);
			stack_size--;
		}
		else
			ft_ra(stack_a);
	}
}

void	ft_shift(t_stack **stack_a)
{
	int	lowest_pos;
	int	stack_size;

	stack_size = ft_stacksize(*stack_a);
	lowest_pos = ft_lowest_position(stack_a);
	if (lowest_pos > stack_size / 2)
	{
		while (lowest_pos < stack_size)
		{
			ft_rra(stack_a);
			lowest_pos++;
		}
	}
	else
	{
		while (lowest_pos > 0)
		{
			ft_ra(stack_a);
			lowest_pos--;
		}
	}
}
