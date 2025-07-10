/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_parse_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:55:21 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/04 14:49:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void		ft_stackadd_back(t_stack **stack_a, t_stack *new);
static t_stack	*ft_stacknew(int nbr);

t_stack	*ft_checker_parse(char **values)
{
	t_stack	*stack_a;
	int		n;
	int		i;

	stack_a = NULL;
	i = 0;
	while (values[i])
	{
		n = ft_atoll(values[i]);
		ft_stackadd_back(&stack_a, ft_stacknew(n));
		i++;
	}
	return (stack_a);
}

static void	ft_stackadd_back(t_stack **stack_a, t_stack *new)
{
	t_stack	*last;

	if (!new)
		return ;
	if (!*stack_a)
	{
		*stack_a = new;
		return ;
	}
	last = *stack_a;
	while (last->next)
		last = last->next;
	last->next = new;
}

static t_stack	*ft_stacknew(int nbr)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->nbr = nbr;
	new->next = NULL;
	return (new);
}
