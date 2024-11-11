/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/11 13:42:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_ptr(void)
{
	int ret;
	int ret_ft;
	int i = 500;
	void	*p = NULL;
	printf("%s--------------------\n- TESTING PTR -\n--------------------%s\n\n", KYEL, KNRM);
	ret = printf("PF: %p\n", &i);
	ret_ft = ft_printf("FT: %p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %p\n", p);
	ret_ft = ft_printf("FT: %p\n", p);
	cmp(ret, ret_ft);

	printf("%s-------------------\nTest 0 with various flags%s\n", KBLU, KNRM);
	ret = printf("PF: %.0p\n", 0);
	ret_ft = ft_printf("FT: %.0p\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %#p\n", 0);
	ret_ft = ft_printf("FT: %#p\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %0p\n", p);
	ret_ft = ft_printf("FT: %0p\n", p);
	cmp(ret, ret_ft);
	ret = printf("PF: %.5p\n", p);
	ret_ft = ft_printf("FT: %.5p\n", p);
	cmp(ret, ret_ft);

	printf("%s-------------------\nPrecision 0 with non-zero numbers%s\n", KBLU, KNRM);
	ret = printf("PF: %.0p\n", &i);
	ret_ft = ft_printf("FT: %.0p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0p\n", &i);
	ret_ft = ft_printf("FT: %.0p\n", &i);
	cmp(ret, ret_ft);

	printf("%s-------------------\nWidth flag:%s\n", KBLU, KNRM);
	ret = printf("PF: %10p\n", &i);
	ret_ft = ft_printf("FT: %10p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %10p\n", &i);
	ret_ft = ft_printf("FT: %10p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %#10p\n", &i);
	ret_ft = ft_printf("FT: %#10p\n", &i);
	cmp(ret, ret_ft);

	printf("%s-------------------\nWidth flag with 0 padding%s\n", KBLU, KNRM);
	ret = printf("PF: %010p\n", &i);
	ret_ft = ft_printf("FT: %010p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %010p\n", &i);
	ret_ft = ft_printf("FT: %010p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %0#10p\n", &i);
	ret_ft = ft_printf("FT: %0#10p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %010p\n", &i);
	ret_ft = ft_printf("FT: %010p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %#010p\n", &i);
	ret_ft = ft_printf("FT: %#010p\n", &i);
	cmp(ret, ret_ft);

	printf("%s-------------------\nLeft-align%s\n", KBLU, KNRM);
	ret = printf("PF: %-10px\n", &i);
	ret_ft = ft_printf("FT: %-10px\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %-10px\n", &i);
	ret_ft = ft_printf("FT: %-10px\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %-#10px\n", &i);
	ret_ft = ft_printf("FT: %-#10px\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %-#10px\n", &i);
	ret_ft = ft_printf("FT: %-#10px\n", &i);
	cmp(ret, ret_ft);

	printf("%s-------------------\nPrecision%s\n", KBLU, KNRM);
	ret = printf("PF: %.0p\n", &i);
	ret_ft = ft_printf("FT: %.0p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %.0p\n", &i);
	ret_ft = ft_printf("FT: %.0p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10p\n", &i);
	ret_ft = ft_printf("FT: %.10p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %.10p\n", &i);
	ret_ft = ft_printf("FT: %.10p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %20.10p\n", &i);
	ret_ft = ft_printf("FT: %20.10p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %-20.10px\n", &i);
	ret_ft = ft_printf("FT: %-20.10px\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %.2p\n", &i);
	ret_ft = ft_printf("FT: %.2p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %#010.5p\n", &i);
	ret_ft = ft_printf("FT: %#010.5p\n", &i);
	cmp(ret, ret_ft);

	printf("%s-------------------\nCombining width, precision, flags%s\n", KBLU, KNRM);
	ret = printf("PF: %#08.5p\n", &i);
	ret_ft = ft_printf("FT: %#08.5p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %#10.5p\n", &i);
	ret_ft = ft_printf("FT: %#10.5p\n", &i);
	cmp(ret, ret_ft);

	printf("%s-------------------\nLarge width and precision:%s\n", KBLU, KNRM);
	ret = printf("PF: %50.30p\n", &i);
	ret_ft = ft_printf("FT: %50.30p\n", &i);
	cmp(ret, ret_ft);

	printf("%s-------------------\nNegative width:%s\n", KBLU, KNRM);
	ret = printf("PF: %-10p\n", &i);
	ret_ft = ft_printf("FT: %-10p\n", &i);
	cmp(ret, ret_ft);

	printf("%s-------------------\nMultiple flags:%s\n", KBLU, KNRM);
	ret = printf("PF: %#-10.5p\n", &i);
	ret_ft = ft_printf("FT: %#-10.5p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %0#10.5p\n", &i);
	ret_ft = ft_printf("FT: %0#10.5p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %#p\n", &i);
	ret_ft = ft_printf("FT: %#p\n", &i);
	cmp(ret, ret_ft);
	printf("%s--------------------\n-  PTR  TEST  ENDS -\n--------------------%s\n", KYEL, KNRM);
}
