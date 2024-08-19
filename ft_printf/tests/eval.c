/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:59:10 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 16:12:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

void	test_eval(void)
{
	int	i = 50;
	int	a;
	int	b;
	char *ptr = NULL;
	ft_printf("----------------------------------------\n");
	ft_printf("Mandatory tests\n\n");
	a = ft_printf("%15i | %15d | %15s | %15c\n", 10, 10, "test", 'c');
	b = printf("%15i | %15d | %15s | %15c\n", 10, 10, "test", 'c');
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("%15x | %15X | %15p | %15u\n\n", 15454, 15454, &i, 10);
	b = printf("%15x | %15X | %15p | %15u\n\n", 15454, 15454, &i, 10);
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("%s\n", "");
	b = printf("%s\n", "");
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("%i\n", -2147483648);
	b = printf("%li\n", -2147483648);
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("%d\n", 0);
	b = printf("%d\n", 0);
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("cspd%iouxX\n", 50);
	b = printf("cspd%iouxX\n", 50);
	printf("orig returns %i and ft returns %i\n\n", b, a);
	ft_printf("%i%i%i%i%i%i%i%ix\n", 1, 1, 1, 1, 1, 1, 1, 1);
	a = ft_printf("cs%pdiouxX\n", ptr);
	b = printf("cs%pdiouxX\n", ptr);
	printf("orig returns %i and ft returns %i\n\n", b, a);

	ft_printf("----------------------------------------\n");
	ft_printf("Bonus tests\n\n");
	a = ft_printf("%.5i\n", 10);
	b = printf("%.5i\n", 10);
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("%.0i\n", 0);
	b = printf("%.0i\n", 0);
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("%.50i\n", 0);
	b = printf("%.50i\n", 0);
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("%-d\n", -2147483648);
	b = printf("%-ld\n", -2147483648);
	printf("orig returns %i and ft returns %i\n\n", b, a);
	a = ft_printf("%04d\n", -2);
	b = printf("%04d\n", -2);
	printf("orig returns %i and ft returns %i\n\n", b, a);
}
