/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:16:58 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/04 20:40:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_rrr_both(t_stack **stack_a, t_stack **stack_b,
				int *cost_a, int *cost_b);
static void	ft_rr_both(t_stack **stack_a, t_stack **stack_b,
				int *cost_a, int *cost_b);
static void	ft_rr_a(t_stack **stack_a, int *cost);
static void	ft_rr_b(t_stack **stack_b, int *cost);

void	ft_move(t_stack **stack_a, t_stack **stack_b, int cost_a, int cost_b)
{
	if (cost_a < 0 && cost_b < 0)
		ft_rrr_both(stack_a, stack_b, &cost_a, &cost_b);
	else if (cost_a > 0 && cost_b > 0)
		ft_rr_both(stack_a, stack_b, &cost_a, &cost_b);
	ft_rr_a(stack_a, &cost_a);
	ft_rr_b(stack_b, &cost_b);
	ft_pa(stack_a, stack_b);
}

static void	ft_rrr_both(t_stack **stack_a, t_stack **stack_b,
			int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		ft_rrr(stack_a, stack_b);
	}
}

static void	ft_rr_both(t_stack **stack_a, t_stack **stack_b,
			int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		ft_rr(stack_a, stack_b);
	}
}

static void	ft_rr_a(t_stack **stack_a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ft_ra(stack_a);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			ft_rra(stack_a);
			(*cost)++;
		}
	}
}

static void	ft_rr_b(t_stack **stack_b, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ft_rb(stack_b);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			ft_rrb(stack_b);
			(*cost)++;
		}
	}
}
