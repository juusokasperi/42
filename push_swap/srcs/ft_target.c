/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_target.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:51:11 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/30 00:31:25 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_position(t_stack **stack);
static int	ft_get_target(t_stack **stack_a, int b_rank,
				int target_rank, int target_position);

void	ft_target(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	int		target;

	tmp = *stack_b;
	ft_position(stack_a);
	ft_position(stack_b);
	target = 0;
	while (tmp)
	{
		target = ft_get_target(stack_a, tmp->rank, INT_MAX, target);
		tmp->target = target;
		tmp = tmp->next;
	}
}

static void	ft_position(t_stack **stack)
{
	t_stack	*tmp;
	int		i;

	tmp = *stack;
	i = 0;
	while (tmp)
	{
		tmp->pos = i++;
		tmp = tmp->next;
	}
}

static int	ft_get_target(t_stack **stack_a, int b_rank,
			int target_rank, int target_position)
{
	t_stack	*tmp;

	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->rank > b_rank && tmp->rank < target_rank)
		{
			target_rank = tmp->rank;
			target_position = tmp->pos;
		}
		tmp = tmp->next;
	}
	if (target_rank != INT_MAX)
		return (target_position);
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->rank < target_rank)
		{
			target_rank = tmp->rank;
			target_position = tmp->pos;
		}
		tmp = tmp->next;
	}
	return (target_position);
}

int	ft_lowest_position(t_stack **stack)
{
	t_stack	*tmp;
	int		lowest_rank;
	int		lowest_pos;

	tmp = *stack;
	lowest_rank = INT_MAX;
	ft_position(stack);
	lowest_pos = tmp->pos;
	while (tmp)
	{
		if (tmp->rank < lowest_rank)
		{
			lowest_rank = tmp->rank;
			lowest_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	return (lowest_pos);
}
