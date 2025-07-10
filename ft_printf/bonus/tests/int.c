/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/14 13:39:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_int(void)
{
	int	ret;
	int	ret_ft;

	printf("%s--------------------\n- TESTING INTEGERS -\n--------------------%s\n",
		KYEL, KNRM);

	ret = printf("PF: %d\n", -2147483648);
	ret_ft = ft_printf("FT: %d\n", -2147483648);
	cmp(ret, ret_ft);
	ret = printf("PF: %d\n", 2147483647);
	ret_ft = ft_printf("FT: %d\n", 2147483647);
	cmp(ret, ret_ft);

	printf("%s--------------------\nTest 0 with various flags\n%s", KBLU, KNRM);
	ret = printf("PF: %.0i\n", 0);
	ret_ft = ft_printf("FT: %.0i\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %+i\n", 0);
	ret_ft = ft_printf("FT: %+i\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: % i\n", 0);
	ret_ft = ft_printf("FT: % i\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %0i\n", 0);
	ret_ft = ft_printf("FT: %0i\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %+.5d\n", 0);
	ret_ft = ft_printf("FT: %+.5d\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: % .5d\n", 0);
	ret_ft = ft_printf("FT: % .5d\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision 0 with non-zero numbers\n%s", KBLU, KNRM);
	ret = printf("PF: %.0d\n", 42);
	ret_ft = ft_printf("FT: %.0d\n", 42);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0d\n", -42);
	ret_ft = ft_printf("FT: %.0d\n", -42);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrinting just ints with no flags\n%s", KBLU, KNRM);
	ret = printf("PF: %i\n", 0);
	ret_ft = ft_printf("FT: %i\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag:\n%s", KBLU, KNRM);
	ret = printf("PF: %10i\n", -10);
	ret_ft = ft_printf("FT: %10i\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %10i\n", 10);
	ret_ft = ft_printf("FT: %10i\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %+10i\n", 10);
	ret_ft = ft_printf("FT: %+10i\n", 10);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag with 0 padding\n%s", KBLU, KNRM);
	ret = printf("PF: %010i\n", -10);
	ret_ft = ft_printf("FT: %010i\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %0 10i\n", 10);
	ret_ft = ft_printf("FT: %0 10i\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %0+10i\n", 10);
	ret_ft = ft_printf("FT: %0+10i\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %010i\n", 10);
	ret_ft = ft_printf("FT: %010i\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %010i\n", 2147483647);
	ret_ft = ft_printf("FT: %010i\n", 2147483647);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLeft-align\n%s", KBLU, KNRM);
	ret = printf("PF: %-10ix\n", -10);
	ret_ft = ft_printf("FT: %-10ix\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-10ix\n", 10);
	ret_ft = ft_printf("FT: %-10ix\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %- 10ix\n", 10);
	ret_ft = ft_printf("FT: %- 10ix\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-+10ix\n", 10);
	ret_ft = ft_printf("FT: %-+10ix\n", 10);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision\n%s", KBLU, KNRM);
	ret = printf("PF: %.0i\n", 15454);
	ret_ft = ft_printf("FT: %.0i\n", 15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0i\n", -15454);
	ret_ft = ft_printf("FT: %.0i\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10i\n", 15454);
	ret_ft = ft_printf("FT: %.10i\n", 15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10i\n", -15454);
	ret_ft = ft_printf("FT: %.10i\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %20.10i\n", -15454);
	ret_ft = ft_printf("FT: %20.10i\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %-20.10ix\n", -15454);
	ret_ft = ft_printf("FT: %-20.10ix\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.2d\n", 123);
	ret_ft = ft_printf("FT: %.2d\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %010.5d\n", 123);
	ret_ft = ft_printf("FT: %010.5d\n", 123);
	cmp(ret, ret_ft);
	ret = printf(" %.2d ", -1);
	printf("\n");
	ret_ft = ft_printf(" %.2d ", -1);
	printf("\n");
	cmp(ret, ret_ft);

	printf("%s--------------------\nCombining width, precision, flags\n%s", KBLU, KNRM);
	ret = printf("PF: %+08.5d\n", 123);
	ret_ft = ft_printf("FT: %+08.5d\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: % 10.5d\n", -123);
	ret_ft = ft_printf("FT: % 10.5d\n", -123);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLarge width and precision:\n%s", KBLU, KNRM);
	ret = printf("PF: %50.30d\n", 123456);
	ret_ft = ft_printf("FT: %50.30d\n", 123456);
	cmp(ret, ret_ft);

	printf("%s--------------------\nNegative width:\n%s", KBLU, KNRM);
	ret = printf("PF: %-10d\n", 42);
	ret_ft = ft_printf("FT: %-10d\n", 42);
	cmp(ret, ret_ft);

	printf("%s--------------------\nMultiple flags:\n%s", KBLU, KNRM);
	ret = printf("PF: %+-10.5d\n", 123);
	ret_ft = ft_printf("FT: %+-10.5d\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %0 +10.5d\n", 123);
	ret_ft = ft_printf("FT: %0 +10.5d\n", 123);
	cmp(ret, ret_ft);

	printf("%s--------------------\n+ -flag:\n%s", KBLU, KNRM);
	ret_ft = ft_printf("FT: %+5d, %+5d, %+5d, %+5d, %+5d, %+5d, %+5d, %+5d\n", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	ret = printf("PF: %+5d, %+5d, %+5d, %+5d, %+5d, %+5d, %+5d, %+5d\n", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	cmp(ret, ret_ft);
	ret_ft = ft_printf("FT: %+5d\n", -1);
	ret = printf("PF: %+5d\n", -1);
	cmp(ret, ret_ft);

	printf("%s--------------------\nSome tricky tests..%s\n", KBLU, KNRM);
	ret = ft_printf("%+.d, %+.d, %+.d, %+.d, %+.d, %+.d, %+.d, %+.d\n", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	ret_ft = printf("%+.d, %+.d, %+.d, %+.d, %+.d, %+.d, %+.d, %+.d\n", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	cmp(ret, ret_ft);

	ret = ft_printf("\001\002\007\v\010\f\r\n");
	ret_ft = printf("\001\002\007\v\010\f\r\n");
	cmp(ret, ret_ft);

	ret = ft_printf("%%\n");
	ret_ft = printf("%%\n");
	cmp(ret, ret_ft);

	ret = ft_printf("%100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X\n", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	ret_ft = printf("%100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X\n", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	cmp(ret, ret_ft);

	printf("%s--------------------\n- INT  TEST ENDS  -\n--------------------\n%s", KYEL, KNRM);
}
