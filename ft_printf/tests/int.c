/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/10 15:52:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	test_int(void)
{
	printf("--------------------\n- TESTING INTEGERS -\n--------------------\n");
	printf("PF: %d\n", -2147483648);
	ft_printf("FT: %d\n", -2147483648);
	printf("PF: %d\n", 2147483647);
	ft_printf("FT: %d\n\n", 2147483647);

	printf("Test 0 with various flags\n");
	printf("PF: %.0i\n", 0);
	ft_printf("FT: %.0i\n", 0);
	printf("PF: %+i\n", 0);
	ft_printf("FT: %+i\n", 0);
	printf("PF: % i\n", 0);
	ft_printf("FT: % i\n", 0);
	printf("PF: %0i\n", 0);
	ft_printf("FT: %0i\n", 0);
	printf("PF: %+.5d\n", 0);
    ft_printf("FT: %+.5d\n", 0);
    printf("PF: % .5d\n", 0);
    ft_printf("FT: % .5d\n\n", 0);

	printf("Precision 0 with non-zero numbers\n");
	printf("PF: %.0d\n", 42);
    ft_printf("FT: %.0d\n", 42);
    printf("PF: %.0d\n", -42);
    ft_printf("FT: %.0d\n\n", -42);

	printf("Printing just ints with no flags\n");
	printf("PF: %i\n", 0);
	ft_printf("FT: %i\n\n", 0);

	printf("Width flag:\n");
	printf("PF: %10i\n", -10);
	ft_printf("FT: %10i\n", -10);
	printf("PF: %10i\n", 10);
	ft_printf("FT: %10i\n", 10);
	printf("PF: %+10i\n", 10);
	ft_printf("FT: %+10i\n\n", 10);

	printf("Width flag with 0 padding\n");
	printf("PF: %010i\n", -10);
	ft_printf("FT: %010i\n", -10);
	printf("PF: %0 10i\n", 10);
	ft_printf("FT: %0 10i\n", 10);
	printf("PF: %0+10i\n", 10);
	ft_printf("FT: %0+10i\n", 10);
	printf("PF: %010i\n", 10);
	ft_printf("FT: %010i\n", 10);
	printf("PF: %010i\n", 2147483647);
	ft_printf("FT: %010i\n\n", 2147483647);

	printf("Left-align\n");
	printf("PF: %-10ix\n", -10);
	ft_printf("FT: %-10ix\n", -10);
	printf("PF: %-10ix\n", 10);
	ft_printf("FT: %-10ix\n", 10);
	printf("PF: %- 10ix\n", 10);
	ft_printf("FT: %- 10ix\n", 10);
	printf("PF: %-+10ix\n", 10);
	ft_printf("FT: %-+10ix\n\n", 10);

	printf("Precision\n");
	printf("PF: %.0i\n", 15454);
	ft_printf("FT: %.0i\n", 15454);
	printf("PF: %.0i\n", -15454);
	ft_printf("FT: %.0i\n", -15454);
	printf("PF: %.10i\n", 15454);
	ft_printf("FT: %.10i\n", 15454);
	printf("PF: %.10i\n", -15454);
	ft_printf("FT: %.10i\n", -15454);
	printf("PF: %20.10i\n", -15454);
	ft_printf("FT: %20.10i\n", -15454);
	printf("PF: %-20.10ix\n", -15454);
	ft_printf("FT: %-20.10ix\n", -15454);
	printf("PF: %.2d\n", 123);
	ft_printf("FT: %.2d\n", 123);
	printf("PF: %010.5d\n", 123);
    ft_printf("FT: %010.5d\n\n", 123);

	printf("Combining width, precision, flags\n");
	printf("PF: %+08.5d\n", 123);
	ft_printf("FT: %+08.5d\n", 123);
	printf("PF: % 10.5d\n", -123);
	ft_printf("FT: % 10.5d\n\n", -123);

	printf("Large width and precision:\n");
	printf("PF: %50.30d\n", 123456);
	ft_printf("FT: %50.30d\n\n", 123456);

	printf("Negative width:\n");
	printf("PF: %-10d\n", 42);
	ft_printf("FT: %-10d\n\n", 42);

	printf("Multiple flags:\n");
	printf("PF: %+-10.5d\n", 123);
	ft_printf("FT: %+-10.5d\n", 123);
	printf("PF: %0 +10.5d\n", 123);
	ft_printf("FT: %0 +10.5d\n\n", 123);
	printf("--------------------\n-    TEST  ENDS    -\n--------------------\n");
}
