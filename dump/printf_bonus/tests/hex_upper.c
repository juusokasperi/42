/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_lower.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/11 16:21:28 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_upper_hex(void)
{
	int ret;
	int ret_ft;
	printf("%s--------------------\n- TESTING U_HEX -\n--------------------%s\n\n", KYEL, KNRM);
	ret = printf("PF: %X\n", -2147483648);
	ret_ft = ft_printf("FT: %X\n", -2147483648);
	cmp(ret, ret_ft);
	ret = printf("PF: %X\n", 2147483647);
	ret_ft = ft_printf("FT: %X\n", 2147483647);
	cmp(ret, ret_ft);
	ret = printf("PF: %X\n", 0);
	ret_ft = ft_printf("FT: %X\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\nTest 0 with various flags%s\n", KBLU, KNRM);
	ret = printf("PF: %.0X\n", 0);
	ret_ft = ft_printf("FT: %.0X\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %#X\n", 0);
	ret_ft = ft_printf("FT: %#X\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %X\n", 0);
	ret_ft = ft_printf("FT: %X\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %0X\n", 0);
	ret_ft = ft_printf("FT: %0X\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %.5X\n", 0);
    ret_ft = ft_printf("FT: %.5X\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision 0 with non-zero numbers:%s\n", KBLU, KNRM);
	ret = printf("PF: %.0X\n", 42);
	ret_ft = ft_printf("FT: %.0X\n", 42);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0X\n", -42);
	ret_ft = ft_printf("FT: %.0X\n", -42);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag:%s\n", KBLU, KNRM);
	ret = printf("PF: %10X\n", -10);
	ret_ft = ft_printf("FT: %10X\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %10X\n", 10);
	ret_ft = ft_printf("FT: %10X\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %#10X\n", 10);
	ret_ft = ft_printf("FT: %#10X\n", 10);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag with 0 padding:%s\n", KBLU, KNRM);
	ret = printf("PF: %010X\n", -10);
	ret_ft = ft_printf("FT: %010X\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %010X\n", 10);
	ret_ft = ft_printf("FT: %010X\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %0#10X\n", 10);
	ret_ft = ft_printf("FT: %0#10X\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %010X\n", 10);
	ret_ft = ft_printf("FT: %010X\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %#010X\n", 2147483647);
	ret_ft = ft_printf("FT: %#010X\n", 2147483647);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLeft-align:%s\n", KBLU, KNRM);
	ret = printf("PF: %-10XX\n", -10);
	ret_ft = ft_printf("FT: %-10XX\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-10XX\n", 10);
	ret_ft = ft_printf("FT: %-10XX\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-#10XX\n", 10);
	ret_ft = ft_printf("FT: %-#10XX\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-#10XX\n", 10);
	ret_ft = ft_printf("FT: %-#10XX\n", 10);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision:%s\n", KBLU, KNRM);
	ret = printf("PF: %.0X\n", 15454);
	ret_ft = ft_printf("FT: %.0X\n", 15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0X\n", -15454);
	ret_ft = ft_printf("FT: %.0X\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10X\n", 15454);
	ret_ft = ft_printf("FT: %.10X\n", 15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10X\n", -15454);
	ret_ft = ft_printf("FT: %.10X\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %20.10X\n", -15454);
	ret_ft = ft_printf("FT: %20.10X\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %-20.10XX\n", -15454);
	ret_ft = ft_printf("FT: %-20.10XX\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.2X\n", 123);
	ret_ft = ft_printf("FT: %.2X\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %#010.5X\n", 123);
	ret_ft = ft_printf("FT: %#010.5X\n", 123);
	cmp(ret, ret_ft);

	printf("%s--------------------\nCombining width, precision, flags:%s\n", KBLU, KNRM);
	ret = printf("PF: %#08.5X\n", 123);
	ret_ft = ft_printf("FT: %#08.5X\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %#10.5X\n", -123);
	ret_ft = ft_printf("FT: %#10.5X\n", -123);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLarge width and precision:%s\n", KBLU, KNRM);
	ret = printf("PF: %50.30X\n", 123456);
	ret_ft = ft_printf("FT: %50.30X\n", 123456);
	cmp(ret, ret_ft);

	printf("%s--------------------\nNegative width:%s\n", KBLU, KNRM);
	ret = printf("PF: %-10X\n", 42);
	ret_ft = ft_printf("FT: %-10X\n", 42);
	cmp(ret, ret_ft);

	printf("%s--------------------\nMultiple flags:%s\n", KBLU, KNRM);
	ret = printf("PF: %#-10.5X\n", 123);
	ret_ft = ft_printf("FT: %#-10.5X\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %0#10.5X\n", 123);
	ret_ft = ft_printf("FT: %0#10.5X\n", 123);
	cmp(ret, ret_ft);
	printf("%s--------------------\n-  U_HEX TEST ENDS -\n--------------------%s\n", KYEL, KNRM);
}
