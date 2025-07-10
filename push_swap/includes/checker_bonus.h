/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:52:10 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/05 01:37:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "libft.h"

typedef struct s_stack
{
	int				nbr;
	struct s_stack	*next;
}	t_stack;

void			ft_stackclear(t_stack **stack_a, t_stack **stack_b);
void			ft_error_free(t_stack **stack_a, t_stack **stack_b);
void			ft_error_free_line(t_stack **stack_a,
					t_stack **stack_b, char *line);
t_stack			*ft_checker_init(int argc, char **argv);
void			**ft_free_split(char **val, char **val_2);
char			**ft_join(char **values, char **new_values);
t_stack			*ft_checker_parse(char **values);
void			ft_pa(t_stack **stack_a, t_stack **stack_b);
void			ft_pb(t_stack **stack_a, t_stack **stack_b);
void			ft_rra(t_stack **stack_a);
void			ft_rrb(t_stack **stack_b);
void			ft_rrr(t_stack **stack_a, t_stack **stack_b);
void			ft_ra(t_stack **stack_a);
void			ft_rb(t_stack **stack_b);
void			ft_rr(t_stack **stack_a, t_stack **stack_b);
void			ft_sa(t_stack **stack_a);
void			ft_sb(t_stack **stack_b);
void			ft_ss(t_stack **stack_a, t_stack **stack_b);
long long int	ft_atoll(const char *str);

#endif
