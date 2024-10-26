/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:19:40 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 15:30:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_iterative_factorial(int nb)
{
	int	i;
	int	temp;

	i = 1;
	temp = 1;
	if (nb < 0)
		return (0);
	while (i <= nb)
	{
		temp = temp * i;
		i++;
	}
	return (temp);
}
