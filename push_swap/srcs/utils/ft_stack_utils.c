/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:55:57 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/29 21:57:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_find_highest(t_stack *stack_a)
{
	t_stack	*tmp;
	int		highest_rank;

	tmp = stack_a;
	highest_rank = stack_a->rank;
	while (tmp)
	{
		if (highest_rank < tmp->rank)
			highest_rank = tmp->rank;
		tmp = tmp->next;
	}
	return (highest_rank);
}

int	ft_find_lowest(t_stack *stack_a)
{
	t_stack	*tmp;
	int		lowest_rank;

	tmp = stack_a;
	lowest_rank = stack_a->rank;
	while (tmp)
	{
		if (lowest_rank > tmp->rank)
			lowest_rank = tmp->rank;
		tmp = tmp->next;
	}
	return (lowest_rank);
}

int	ft_stacksize(t_stack *stack)
{
	t_stack	*ptr;
	int		count;

	ptr = stack;
	count = 0;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

t_stack	*ft_stacklast(t_stack *stack)
{
	t_stack	*ptr;

	if (!stack)
		return (NULL);
	ptr = stack;
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	return (ptr);
}
