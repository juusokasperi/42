/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:44:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/30 00:37:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_sort_three(t_stack **stack_a);
static void		ft_sort_big(t_stack **stack_a);
static void		ft_biggest_three(t_stack **stack_a, t_stack **stack_b,
					int stack_size, int values_pushed);
static void		ft_shift(t_stack **stack_a);

void	ft_sort(t_stack **stack_a)
{
	if (ft_stacksize(*stack_a) == 2)
		ft_sa(stack_a);
	else if (ft_stacksize(*stack_a) == 3)
		ft_sort_three(stack_a);
	else
		ft_sort_big(stack_a);
}

static void	ft_sort_big(t_stack **stack_a)
{
	t_stack	*stack_b;

	stack_b = NULL;
	ft_biggest_three(stack_a, &stack_b, ft_stacksize(*stack_a), 0);
	if (!ft_is_sorted(*stack_a))
		ft_sort_three(stack_a);
	while (stack_b)
	{
		ft_target(stack_a, &stack_b);
		ft_calculate(stack_a, &stack_b);
		ft_execute(stack_a, &stack_b);
	}
	if (!ft_is_sorted(*stack_a))
		ft_shift(stack_a);
	ft_stackclear(&stack_b);
}

static void	ft_biggest_three(t_stack **stack_a, t_stack **stack_b,
		int stack_size, int values_pushed)
{
	int	highest_rank;
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

static void	ft_sort_three(t_stack **stack_a)
{
	int	lowest_rank;
	int	highest_rank;

	lowest_rank = ft_find_lowest(*stack_a);
	highest_rank = ft_find_highest(*stack_a);
	if ((*stack_a)->rank == lowest_rank)
	{
		ft_rra(stack_a);
		ft_sa(stack_a);
	}
	else if ((*stack_a)->rank == highest_rank)
	{
		ft_ra(stack_a);
		if (!ft_is_sorted(*stack_a))
			ft_sa(stack_a);
	}
	else
	{
		if (ft_stacklast(*stack_a)->rank == highest_rank)
			ft_sa(stack_a);
		else
			ft_rra(stack_a);
	}
}

static void	ft_shift(t_stack **stack_a)
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
