/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:44:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/28 01:01:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				ft_stacksize(t_stack *stack);
static t_stack	*ft_stacklast(t_stack *stack);
static void		ft_sort_three(t_stack **stack_a);

void	ft_sort(t_stack **stack_a)
{
	t_stack	*stack_b;
	int		i;

	stack_b = NULL;
	if (ft_stacksize(*stack_a) == 2)
		ft_sa(stack_a);
	else if (ft_stacksize(*stack_a) == 3)
		ft_sort_three(stack_a);
}

static void	ft_sort_three(t_stack **stack_a)
{
	if ((*stack_a)->rank == 0)
	{
		ft_rra(stack_a);
		ft_sa(stack_a);
	}
	else if ((*stack_a)->rank == 2)
	{
		ft_ra(stack_a);
		if (!ft_is_sorted(*stack_a))
			ft_sa(stack_a);
	}
	else
	{
		if (ft_stacklast(*stack_a)->rank == 2)
			ft_sa(stack_a);
		else
			ft_rra(stack_a);
	}
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

static t_stack	*ft_stacklast(t_stack *stack)
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
