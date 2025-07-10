/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:36:44 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/04 14:46:56 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	ft_is_sorted(t_stack *stack);
static void	ft_operation(t_stack **stack_a, t_stack **stack_b, char *line);

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	*line;

	if (argc < 2)
		return (1);
	stack_a = ft_checker_init(argc, argv);
	if (!stack_a)
		ft_error_free(&stack_a, NULL);
	stack_b = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		ft_operation(&stack_a, &stack_b, line);
		free(line);
	}
	if (!ft_is_sorted(stack_a) || stack_b)
		ft_putstr_fd("KO\n", 1);
	else
		ft_putstr_fd("OK\n", 1);
	ft_stackclear(&stack_a, &stack_b);
	return (0);
}

static void	ft_operation(t_stack **stack_a, t_stack **stack_b, char *line)
{
	if (!ft_strncmp(line, "sa", 2) && ft_strlen(line) == 3)
		ft_sa(stack_a);
	else if (!ft_strncmp(line, "sb", 2) && ft_strlen(line) == 3)
		ft_sb(stack_b);
	else if (!ft_strncmp(line, "ss", 2) && ft_strlen(line) == 3)
		ft_ss(stack_a, stack_b);
	else if (!ft_strncmp(line, "pa", 2) && ft_strlen(line) == 3)
		ft_pa(stack_a, stack_b);
	else if (!ft_strncmp(line, "pb", 2) && ft_strlen(line) == 3)
		ft_pb(stack_a, stack_b);
	else if (!ft_strncmp(line, "ra", 2) && ft_strlen(line) == 3)
		ft_ra(stack_a);
	else if (!ft_strncmp(line, "rb", 2) && ft_strlen(line) == 3)
		ft_rb(stack_b);
	else if (!ft_strncmp(line, "rr", 2) && ft_strlen(line) == 3)
		ft_rr(stack_a, stack_b);
	else if (!ft_strncmp(line, "rra", 3) && ft_strlen(line) == 4)
		ft_rra(stack_a);
	else if (!ft_strncmp(line, "rrb", 3) && ft_strlen(line) == 4)
		ft_rrb(stack_b);
	else if (!ft_strncmp(line, "rrr", 3) && ft_strlen(line) == 4)
		ft_rrr(stack_a, stack_b);
	else
		ft_error_free_line(stack_a, stack_b, line);
}

void	ft_stackclear(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;

	if (!stack_a || !*stack_a)
		return ;
	while (*stack_a)
	{
		tmp = (*stack_a)->next;
		free(*stack_a);
		*stack_a = tmp;
	}
	*stack_a = NULL;
	if (!stack_b || !*stack_b)
		return ;
	while (*stack_b)
	{
		tmp = (*stack_b)->next;
		free(*stack_b);
		*stack_b = tmp;
	}
	*stack_b = NULL;
}

static int	ft_is_sorted(t_stack *stack)
{
	while (stack->next)
	{
		if (stack->nbr > stack->next->nbr)
			return (0);
		stack = stack->next;
	}
	return (1);
}
