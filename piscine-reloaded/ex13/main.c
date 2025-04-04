/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:31:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 15:49:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_recursive_factorial(int nb);

int	main(void)
{
	int	i;

	i = ft_recursive_factorial(0);
	printf("Iterative of 0 is %i\n", i);
	i = ft_recursive_factorial(5);
	printf("Iterative of 5 is %i\n", i);
	return (0);
}
