/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_target.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:51:11 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/10 18:10:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_current_position(t_stack **stack);
static int	ft_get_target(t_stack **stack_a, int b_rank);

void	ft_target(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp_b;
	int		target;

	tmp_b = *stack_b;
	ft_current_position(stack_a);
	ft_current_position(stack_b);
	while (tmp_b)
	{
		target = ft_get_target(stack_a, tmp_b->rank);
		tmp_b->target = target;
		tmp_b = tmp_b->next;
	}
}

static void	ft_current_position(t_stack **stack)
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

static int	ft_get_target(t_stack **stack_a, int b_rank)
{
	t_stack	*tmp_a;
	int		target_position;
	int		target_rank;

	tmp_a = *stack_a;
	target_position = 0;
	target_rank = INT_MAX;
	while (tmp_a)
	{
		if (tmp_a->rank > b_rank && tmp_a->rank < target_rank)
		{
			target_rank = tmp_a->rank;
			target_position = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	return (target_position);
}

int	ft_lowest_position(t_stack **stack)
{
	t_stack	*tmp;
	int		lowest_rank;
	int		lowest_pos;

	tmp = *stack;
	lowest_rank = tmp->rank;
	ft_current_position(stack);
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
