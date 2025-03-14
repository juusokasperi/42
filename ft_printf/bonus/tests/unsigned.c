/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/13 16:28:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_unsigned(void)
{
	int	ret;
	int	ret_ft;
	printf("%s--------------------\n- TESTING UNSIGNED -\n--------------------\n%s", KYEL, KNRM);
	ret = printf("PF: %u\n", -10);
	ret_ft = ft_printf("FT: %u\n", -10);
	cmp(ret, ret_ft);

	ret = printf("PF: %u\n", 2147483647);
	ret_ft = ft_printf("FT: %u\n", 2147483647);
	cmp(ret, ret_ft);

	printf("%s--------------------\nTest 0 with various flags\n%s", KBLU, KNRM);
	ret = printf("PF: %.0u\n", 0);
	ret_ft = ft_printf("FT: %.0u\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %+u\n", 0);
	ret_ft = ft_printf("FT: %+u\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: % u\n", 0);
	ret_ft = ft_printf("FT: % u\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %0u\n", 0);
	ret_ft = ft_printf("FT: %0u\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %+.5u\n", 0);
	ret_ft = ft_printf("FT: %+.5u\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: % .5u\n", 0);
	ret_ft = ft_printf("FT: % .5u\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision 0 with non-zero numbers\n%s", KBLU, KNRM);
	ret = printf("PF: %.0u\n", 42);
	ret_ft = ft_printf("FT: %.0u\n", 42);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0u\n", -42);
	ret_ft = ft_printf("FT: %.0u\n", -42);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrinting just ints with no flags\n%s", KBLU, KNRM);
	ret = printf("PF: %u\n", 0);
	ret_ft = ft_printf("FT: %u\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag:\n%s", KBLU, KNRM);
	ret = printf("PF: %10u\n", -10);
	ret_ft = ft_printf("FT: %10u\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %10u\n", 10);
	ret_ft = ft_printf("FT: %10u\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %+10u\n", 10);
	ret_ft = ft_printf("FT: %+10u\n", 10);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag with 0 padding\n%s", KBLU, KNRM);
	ret = printf("PF: %010u\n", -10);
	ret_ft = ft_printf("FT: %010u\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %0 10u\n", 10);
	ret_ft = ft_printf("FT: %0 10u\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %0+10u\n", 10);
	ret_ft = ft_printf("FT: %0+10u\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %010u\n", 10);
	ret_ft = ft_printf("FT: %010u\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %010u\n", 2147483647);
	ret_ft = ft_printf("FT: %010u\n", 2147483647);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLeft-align\n%s", KBLU, KNRM);
	ret = printf("PF: %-10ux\n", -10);
	ret_ft = ft_printf("FT: %-10ux\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-10ux\n", 10);
	ret_ft = ft_printf("FT: %-10ux\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %- 10ux\n", 10);
	ret_ft = ft_printf("FT: %- 10ux\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-+10ux\n", 10);
	ret_ft = ft_printf("FT: %-+10ux\n", 10);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision\n%s", KBLU, KNRM);
	ret = printf("PF: %.0u\n", 15454);
	ret_ft = ft_printf("FT: %.0u\n", 15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0u\n", -15454);
	ret_ft = ft_printf("FT: %.0u\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10u\n", 15454);
	ret_ft = ft_printf("FT: %.10u\n", 15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10u\n", -15454);
	ret_ft = ft_printf("FT: %.10u\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %20.10u\n", -15454);
	ret_ft = ft_printf("FT: %20.10u\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %-20.10ux\n", -15454);
	ret_ft = ft_printf("FT: %-20.10ux\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.2u\n", 123);
	ret_ft = ft_printf("FT: %.2u\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %010.5u\n", 123);
    ret_ft = ft_printf("FT: %010.5u\n", 123);
	cmp(ret, ret_ft);

	printf("%s--------------------\nCombining width, precision, flags\n%s", KBLU, KNRM);
	ret = printf("PF: %+08.5u\n", 123);
	ret_ft = ft_printf("FT: %+08.5u\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: % 10.5u\n", -123);
	ret_ft = ft_printf("FT: % 10.5u\n", -123);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLarge width and precision:\n%s", KBLU, KNRM);
	ret = printf("PF: %50.30u\n", 123456);
	ret_ft = ft_printf("FT: %50.30u\n", 123456);
	cmp(ret, ret_ft);

	printf("%s--------------------\nNegative width:\n%s", KBLU, KNRM);
	ret = printf("PF: %-10u\n", 42);
	ret_ft = ft_printf("FT: %-10u\n", 42);
	cmp(ret, ret_ft);

	printf("%s--------------------\nMultiple flags:\n%s", KBLU, KNRM);
	ret = printf("PF: %+-10.5u\n", 123);
	ret_ft = ft_printf("FT: %+-10.5u\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %0 +10.5u\n", 123);
	ret_ft = ft_printf("FT: %0 +10.5u\n", 123);
	cmp(ret, ret_ft);
	printf("%s--------------------\n- UNSIGN TEST ENDS -\n--------------------\n%s", KYEL, KNRM);
}
