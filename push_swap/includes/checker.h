/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:52:10 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/02 12:44:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft.h"

typedef struct s_stack
{
	int				nbr;
	struct s_stack	*next;
} t_stack;

t_stack			*ft_checker_init(int argc, char **argv);
t_stack			*ft_checker_parse(char **values);
void			ft_error_free(t_stack **stack_a, t_stack **stack_b);
long long int	ft_atoll(const char *str);
//Moves:
void	ft_sa(t_stack **stack_a);
void	ft_sb(t_stack **stack_b);
void	ft_ss(t_stack **stack_a, t_stack **stack_b);
void	ft_ra(t_stack **stack_a);
void	ft_rb(t_stack **stack_b);
void	ft_rr(t_stack **stack_a, t_stack **stack_b);
void	ft_rra(t_stack **stack_a);
void	ft_rrb(t_stack **stack_b);
void	ft_rrr(t_stack **stack_a, t_stack **stack_b);
void	ft_pa(t_stack **stack_a, t_stack **stack_b);
void	ft_pb(t_stack **stack_a, t_stack **stack_b);

#endif
