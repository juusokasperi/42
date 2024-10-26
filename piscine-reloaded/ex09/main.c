/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:46:07 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 14:49:24 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	ft_ft(int *nbr);

int	main(void)
{
	int	i;

	i = 10;
	printf("Before ft_ft() i is %i\n", i);
	ft_ft(&i);
	printf("After ft_ft() i is %i\n", i);
	return (0);
}
