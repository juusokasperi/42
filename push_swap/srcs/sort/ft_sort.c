/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:44:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/06 02:07:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_sort_three(t_stack **stack_a);
static void		ft_sort_big(t_stack **stack_a);
static void		ft_sort_five(t_stack **stack_a);
static void		ft_sort_four(t_stack **stack_a);

void	ft_sort(t_stack **stack_a)
{
	if (ft_stacksize(*stack_a) == 2)
		ft_sa(stack_a);
	else if (ft_stacksize(*stack_a) == 3)
		ft_sort_three(stack_a);
	else if (ft_stacksize(*stack_a) == 4)
		ft_sort_four(stack_a);
	else if (ft_stacksize(*stack_a) == 5)
		ft_sort_five(stack_a);
	else
		ft_sort_big(stack_a);
}

static void	ft_sort_four(t_stack **stack_a)
{
	t_stack	*stack_b;

	stack_b = NULL;
	if ((*stack_a)->next->rank == ft_find_lowest(*stack_a))
		ft_sa(stack_a);
	else if (ft_stacklast(*stack_a)->rank == ft_find_lowest(*stack_a))
		ft_rra(stack_a);
	else if ((*stack_a)->next->next->rank == ft_find_lowest(*stack_a))
	{
		ft_ra(stack_a);
		ft_ra(stack_a);
	}
	if (!ft_is_sorted(*stack_a))
	{
		ft_pb(stack_a, &stack_b);
		if (!ft_is_sorted(*stack_a))
			ft_sort_three(stack_a);
		ft_pa(stack_a, &stack_b);
	}
}

static void	ft_sort_five(t_stack **stack_a)
{
	t_stack	*stack_b;

	stack_b = NULL;
	while (ft_stacksize(*stack_a) > 3)
	{
		ft_sort_five_helper(stack_a);
		ft_pb(stack_a, &stack_b);
	}
	if (!ft_is_sorted(*stack_a))
		ft_sort_three(stack_a);
	if ((stack_b)->rank < (stack_b)->next->rank)
		ft_sb(&stack_b);
	ft_pa(stack_a, &stack_b);
	ft_pa(stack_a, &stack_b);
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
