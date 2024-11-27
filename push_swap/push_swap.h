/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:10:47 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/28 01:05:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <limits.h>
# include <unistd.h>

typedef struct s_stack
{
	int				nbr;
	int				rank;
	struct s_stack	*next;
} t_stack;

//Init:
long long int	ft_atoll(const char *str);
void			ft_error_free(t_stack **stack_a, t_stack **stack_b);
t_stack			*ft_init(int argc, char **argv);
t_stack			*ft_parse_stack(char **values);
void			ft_stackclear(t_stack **stack);
//Sort:
int				ft_is_sorted(t_stack *stack);
void			ft_sort(t_stack **stack_a);

//Operations:
void	ft_sa(t_stack **stack_a);
void	ft_sb(t_stack **stack_b);
void	ft_ss(t_stack **stack_a, t_stack **stack_b);
void	ft_pa(t_stack **stack_a, t_stack **stack_b);
void	ft_pb(t_stack **stack_a, t_stack **stack_b);
void	ft_ra(t_stack **stack_a);
void	ft_rb(t_stack **stack_b);
void	ft_rr(t_stack **stack_a, t_stack **stack_b);
void	ft_rra(t_stack **stack_a);
void	ft_rrb(t_stack **stack_b);
void	ft_rrr(t_stack **stack_a, t_stack **stack_b);

#endif
