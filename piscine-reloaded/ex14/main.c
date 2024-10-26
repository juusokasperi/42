/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:39:15 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 17:48:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>

int	ft_sqrt(int nb);

int	main(void)
{
	clock_t	start;
	clock_t	end;
	double	cpu_time_used;
	int		i;

	start = clock();
	i = ft_sqrt(250000000);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Sqrt of 250000000 is %i\n", i);
	printf("Exec time is: %f seconds \n", cpu_time_used);
	return (0);
}
