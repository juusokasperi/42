/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 16:12:20 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

void	test_unsigned(void)
{
	printf("--------------------\n- TESTING UNSIGNED -\n--------------------\n");
//	printf("PF: %u\n", -2147483648);
//	ft_printf("FT: %u\n", -2147483648);
	printf("PF: %u\n", 2147483647);
	ft_printf("FT: %u\n\n", 2147483647);

	printf("Test 0 with various flags\n");
	printf("PF: %.0u\n", 0);
	ft_printf("FT: %.0u\n", 0);
//	printf("PF: %+u\n", 0);
//	ft_printf("FT: %+u\n", 0);
//	printf("PF: % u\n", 0);
//	ft_printf("FT: % u\n", 0);
	printf("PF: %0u\n", 0);
	ft_printf("FT: %0u\n", 0);
//	printf("PF: %+.5u\n", 0);
//  ft_printf("FT: %+.5u\n", 0);
//	printf("PF: % .5u\n", 0);
//	ft_printf("FT: % .5u\n\n", 0);

	printf("Precision 0 with non-zero numbers\n");
	printf("PF: %.0u\n", 42);
	ft_printf("FT: %.0u\n", 42);
	printf("PF: %.0u\n", -42);
	ft_printf("FT: %.0u\n\n", -42);

	printf("Printing just ints with no flags\n");
	printf("PF: %u\n", 0);
	ft_printf("FT: %u\n\n", 0);

	printf("Width flag:\n");
	printf("PF: %10u\n", -10);
	ft_printf("FT: %10u\n", -10);
	printf("PF: %10u\n", 10);
	ft_printf("FT: %10u\n", 10);
//	printf("PF: %+10u\n", 10);
//	ft_printf("FT: %+10u\n\n", 10);

	printf("Width flag with 0 padding\n");
	printf("PF: %010u\n", -10);
	ft_printf("FT: %010u\n", -10);
//	printf("PF: %0 10u\n", 10);
//	ft_printf("FT: %0 10u\n", 10);
//	printf("PF: %0+10u\n", 10);
//	ft_printf("FT: %0+10u\n", 10);
	printf("PF: %010u\n", 10);
	ft_printf("FT: %010u\n", 10);
	printf("PF: %010u\n", 2147483647);
	ft_printf("FT: %010u\n\n", 2147483647);

	printf("Left-align\n");
	printf("PF: %-10ux\n", -10);
	ft_printf("FT: %-10ux\n", -10);
	printf("PF: %-10ux\n", 10);
	ft_printf("FT: %-10ux\n", 10);
//	printf("PF: %- 10ux\n", 10);
//	ft_printf("FT: %- 10ux\n", 10);
//	printf("PF: %-+10ux\n", 10);
//	ft_printf("FT: %-+10ux\n\n", 10);

	printf("Precision\n");
	printf("PF: %.0u\n", 15454);
	ft_printf("FT: %.0u\n", 15454);
	printf("PF: %.0u\n", -15454);
	ft_printf("FT: %.0u\n", -15454);
	printf("PF: %.10u\n", 15454);
	ft_printf("FT: %.10u\n", 15454);
	printf("PF: %.10u\n", -15454);
	ft_printf("FT: %.10u\n", -15454);
	printf("PF: %20.10u\n", -15454);
	ft_printf("FT: %20.10u\n", -15454);
	printf("PF: %-20.10ux\n", -15454);
	ft_printf("FT: %-20.10ux\n", -15454);
	printf("PF: %.2u\n", 123);
	ft_printf("FT: %.2u\n", 123);
	printf("PF: %010.5u\n", 123);
    ft_printf("FT: %010.5u\n\n", 123);

//	printf("Combining width, precision, flags\n");
//	printf("PF: %+08.5u\n", 123);
//	ft_printf("FT: %+08.5u\n", 123);
//	printf("PF: % 10.5u\n", -123);
//	ft_printf("FT: % 10.5u\n\n", -123);

	printf("Large width and precision:\n");
	printf("PF: %50.30u\n", 123456);
	ft_printf("FT: %50.30u\n\n", 123456);

	printf("Negative width:\n");
	printf("PF: %-10u\n", 42);
	ft_printf("FT: %-10u\n\n", 42);

//	printf("Multiple flags:\n");
//	printf("PF: %+-10.5u\n", 123);
//	ft_printf("FT: %+-10.5u\n", 123);
//	printf("PF: %0 +10.5u\n", 123);
//	ft_printf("FT: %0 +10.5u\n\n", 123);
	printf("--------------------\n- UNSIGN TEST ENDS -\n--------------------\n");
}
