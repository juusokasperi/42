/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:49:59 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 14:52:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_swap(int *a, int *b);

int	main(void)
{
	int	a;
	int	b;

	a = -5;
	b = 42;
	printf("Before ft_swap() a is %i and b is %i\n", a, b);
	ft_swap(&a, &b);
	printf("After ft_swap() a is %i and b is %i\n", a, b);
	return (0);
}
