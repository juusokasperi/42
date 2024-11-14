/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 17:40:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_str(void)
{
	int	ret;
	int	ret_ft;
	printf("%s--------------------\n-  TESTING STRING  -\n--------------------\n%s", KYEL, KNRM);
	ret = printf("PF: %s\n", (char *)NULL);
	ret_ft = ft_printf("FT: %s\n", (char *)NULL);
	cmp(ret, ret_ft);

	char *str = "Test String";
	ret = printf("PF: %s\n", str);
	ret_ft = ft_printf("FT: %s\n", str);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag:\n%s", KBLU, KNRM);
	ret = printf("PF: x%020s\n", str);
	ret_ft = ft_printf("FT: x%020s\n", str);
	cmp(ret, ret_ft);
	ret = printf("PF: %5s\n", str);
	ret_ft = ft_printf("FT: %5s\n", str);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLeft-align\n%s", KBLU, KNRM);
	ret = printf("PF: %-20sx\n", str);
	ret_ft = ft_printf("FT: %-20sx\n", str);
	cmp(ret, ret_ft);

	printf("%s--------------------\nPrecision 0\n%s", KBLU, KNRM);
	ret = printf("PF: %.0s\n", str);
	ret_ft = ft_printf("FT: %.0s\n", str);
	cmp(ret, ret_ft);

	printf("%s--------------------\nOther precision and combinations\n%s", KBLU, KNRM);
	ret = printf("PF: %.5s\n", str);
	ret_ft = ft_printf("FT: %.5s\n", str);
	cmp(ret, ret_ft);
	ret = printf("PF: %.50s\n", str);
	ret_ft = ft_printf("FT: %.50s\n", str);
	cmp(ret, ret_ft);
	ret = printf("PF: %20.10s\n", str);
	ret_ft = ft_printf("FT: %20.10s\n", str);
	cmp(ret, ret_ft);
	ret = printf("PF: %-20.10sx\n", str);
	ret_ft = ft_printf("FT: %-20.10sx\n", str);
	cmp(ret, ret_ft);

	printf("%s--------------------\nUnprintables\n%s", KBLU, KNRM);
	ret = printf("PF: \001\002\007\v\010\f\r\n");
	ret_ft = ft_printf("FT: \001\002\007\v\010\f\r\n");
	cmp(ret, ret_ft);

	ret = printf("1-> PF: %.50p\n", &str);
	ret = printf("2-> PF: %.5p\n", &str);
	ret = printf("3-> PF: %50p\n", &str);
	ret = printf("x-> PF: %-50p\n", &str);
	ret = printf("4-> PF: %5.50p\n", &str);
	ret = printf("5-> PF: %050.5p\n", &str);
	ret = printf("y-> PF: %50.5p\n", &str);
	ret = printf("6-> PF: %050p\n", &str);
	ret = printf("z-> PF: %050.25p\n", &str);
	ret = printf("Z-> PF: %050.25p\n", &str);
	ret = printf("7-> PF: %05p\n", &str);
	ret = printf("8-> PF: %5p\n", &str);
	ret = printf("9-> PF: %-50.30p\n", &str);
	ret = printf("A-> PF: %-.50p\n", &str);
	ret = printf("B-> PF: %.50p\n", &str);


	printf("%s--------------------\n- STRING TEST ENDS -\n--------------------\n%s", KYEL, KNRM);
}
