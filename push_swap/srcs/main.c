/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 00:14:44 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/04 15:31:56 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;

	if (argc < 2)
		return (1);
	stack_a = ft_init(argc, argv);
	if (!stack_a)
		ft_error_free(NULL, NULL);
	if (!ft_is_sorted(stack_a))
		ft_sort(&stack_a);
	ft_stackclear(&stack_a);
	return (0);
}

void	ft_error_free(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_a && *stack_a)
		ft_stackclear(stack_a);
	if (stack_b && *stack_b)
		ft_stackclear(stack_b);
	write(2, "Error\n", 6);
	exit (1);
}

void	ft_stackclear(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

int	ft_is_sorted(t_stack *stack)
{
	while (stack->next)
	{
		if (stack->nbr > stack->next->nbr)
			return (0);
		stack = stack->next;
	}
	return (1);
}
