/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_lower.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/11 16:22:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_lower_hex(void)
{
	int ret;
	int ret_ft;
	printf("%s--------------------\n- TESTING L_HEX -\n--------------------%s\n\n", KYEL, KNRM);
	ret = printf("PF: %x\n", -2147483648);
	ret_ft = ft_printf("FT: %x\n", -2147483648);
	cmp(ret, ret_ft);
	ret = printf("PF: %x\n", 2147483647);
	ret_ft = ft_printf("FT: %x\n", 2147483647);
	cmp(ret, ret_ft);
	ret = printf("PF: %x\n", 0);
	ret_ft = ft_printf("FT: %x\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\nTest 0 with various flags%s\n", KBLU, KNRM);
	ret = printf("PF: %.0x\n", 0);
	ret_ft = ft_printf("FT: %.0x\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %#x\n", 0);
	ret_ft = ft_printf("FT: %#x\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %x\n", 0);
	ret_ft = ft_printf("FT: %x\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %0x\n", 0);
	ret_ft = ft_printf("FT: %0x\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %.5x\n", 0);
    ret_ft = ft_printf("FT: %.5x\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision 0 with non-zero numbers:%s\n", KBLU, KNRM);
	ret = printf("PF: %.0x\n", 42);
	ret_ft = ft_printf("FT: %.0x\n", 42);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0x\n", -42);
	ret_ft = ft_printf("FT: %.0x\n", -42);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag:%s\n", KBLU, KNRM);
	ret = printf("PF: %10x\n", -10);
	ret_ft = ft_printf("FT: %10x\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %10x\n", 10);
	ret_ft = ft_printf("FT: %10x\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %#10x\n", 10);
	ret_ft = ft_printf("FT: %#10x\n", 10);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag with 0 padding:%s\n", KBLU, KNRM);
	ret = printf("PF: %010x\n", -10);
	ret_ft = ft_printf("FT: %010x\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %010x\n", 10);
	ret_ft = ft_printf("FT: %010x\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %0#10x\n", 10);
	ret_ft = ft_printf("FT: %0#10x\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %010x\n", 10);
	ret_ft = ft_printf("FT: %010x\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %#010x\n", 2147483647);
	ret_ft = ft_printf("FT: %#010x\n", 2147483647);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLeft-align:%s\n", KBLU, KNRM);
	ret = printf("PF: %-10xx\n", -10);
	ret_ft = ft_printf("FT: %-10xx\n", -10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-10xx\n", 10);
	ret_ft = ft_printf("FT: %-10xx\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-#10xx\n", 10);
	ret_ft = ft_printf("FT: %-#10xx\n", 10);
	cmp(ret, ret_ft);
	ret = printf("PF: %-#10xx\n", 10);
	ret_ft = ft_printf("FT: %-#10xx\n", 10);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision:%s\n", KBLU, KNRM);
	ret = printf("PF: %.0x\n", 15454);
	ret_ft = ft_printf("FT: %.0x\n", 15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0x\n", -15454);
	ret_ft = ft_printf("FT: %.0x\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10x\n", 15454);
	ret_ft = ft_printf("FT: %.10x\n", 15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10x\n", -15454);
	ret_ft = ft_printf("FT: %.10x\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %20.10x\n", -15454);
	ret_ft = ft_printf("FT: %20.10x\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %-20.10xx\n", -15454);
	ret_ft = ft_printf("FT: %-20.10xx\n", -15454);
	cmp(ret, ret_ft);
	ret = printf("PF: %.2x\n", 123);
	ret_ft = ft_printf("FT: %.2x\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %#010.5x\n", 123);
	ret_ft = ft_printf("FT: %#010.5x\n", 123);
	cmp(ret, ret_ft);

	printf("%s--------------------\nCombining width, precision, flags:%s\n", KBLU, KNRM);
	ret = printf("PF: %#08.5x\n", 123);
	ret_ft = ft_printf("FT: %#08.5x\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %#10.5x\n", -123);
	ret_ft = ft_printf("FT: %#10.5x\n", -123);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLarge width and precision:%s\n", KBLU, KNRM);
	ret = printf("PF: %50.30x\n", 123456);
	ret_ft = ft_printf("FT: %50.30x\n", 123456);
	cmp(ret, ret_ft);

	printf("%s--------------------\nNegative width:%s\n", KBLU, KNRM);
	ret = printf("PF: %-10x\n", 42);
	ret_ft = ft_printf("FT: %-10x\n", 42);
	cmp(ret, ret_ft);

	printf("%s--------------------\nMultiple flags:%s\n", KBLU, KNRM);
	ret = printf("PF: %#-10.5x\n", 123);
	ret_ft = ft_printf("FT: %#-10.5x\n", 123);
	cmp(ret, ret_ft);
	ret = printf("PF: %0#10.5x\n", 123);
	ret_ft = ft_printf("FT: %0#10.5x\n", 123);
	cmp(ret, ret_ft);
	printf("%s--------------------\n-  L_HEX TEST ENDS -\n--------------------%s\n", KYEL, KNRM);
}
