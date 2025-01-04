/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:10:47 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/05 01:25:30 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_stack
{
	int				nbr;
	int				rank;
	int				pos;
	int				target;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_stack;

//	Init:
t_stack			*ft_init(int argc, char **argv);
char			**ft_join(char **values, char **new_values);
void			**ft_free_split(char **val, char **val_2);
long long int	ft_atoll(const char *str);
t_stack			*ft_parse_stack(char **values);
//	Sort:
int				ft_is_sorted(t_stack *stack);
void			ft_sort(t_stack **stack_a);
//	Stack utilities:
int				ft_stacksize(t_stack *stack);
t_stack			*ft_stacklast(t_stack *stack);
int				ft_find_highest(t_stack *stack_a);
int				ft_find_lowest(t_stack *stack_a);
//	Bigger sort, calculate target and costs and execute:
void			ft_target(t_stack **stack_a, t_stack **stack_b);
void			ft_calculate(t_stack **stack_a, t_stack **stack_b);
void			ft_execute(t_stack **stack_a, t_stack **stack_b);
void			ft_move(t_stack **stack_a,
					t_stack **stack_b, int cost_a, int cost_b);
int				ft_lowest_position(t_stack **stack);
void			ft_sort_five_helper(t_stack **stack_a);
void			ft_biggest_three(t_stack **stack_a, t_stack **stack_b,
					int stack_size, int values_pushed);
void			ft_shift(t_stack **stack_a);
//	Cleanup:
void			ft_error_free(t_stack **stack_a, t_stack **stack_b);
void			ft_stackclear(t_stack **stack);
//	Operations:
void			ft_sa(t_stack **stack_a);
void			ft_sb(t_stack **stack_b);
void			ft_ss(t_stack **stack_a, t_stack **stack_b);
void			ft_pa(t_stack **stack_a, t_stack **stack_b);
void			ft_pb(t_stack **stack_a, t_stack **stack_b);
void			ft_ra(t_stack **stack_a);
void			ft_rb(t_stack **stack_b);
void			ft_rr(t_stack **stack_a, t_stack **stack_b);
void			ft_rra(t_stack **stack_a);
void			ft_rrb(t_stack **stack_b);
void			ft_rrr(t_stack **stack_a, t_stack **stack_b);

#endif
