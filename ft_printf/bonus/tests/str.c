/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/15 10:23:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_str(void)
{
	char *str = "Test String";
	int	ret;
	int	ret_ft;
	printf("%s--------------------\n-  TESTING STRING  -\n--------------------\n%s", KYEL, KNRM);
	ret = printf("PF: %s\n", (char *)NULL);
	ret_ft = ft_printf("FT: %s\n", (char *)NULL);
	cmp(ret, ret_ft);


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

	ret = printf(" NULL %s NULL ", NULL);
	printf("\n");
	ret_ft = ft_printf(" NULL %s NULL ", NULL);
	printf("\n");
	cmp(ret, ret_ft);

	printf("%s--------------------\n- STRING TEST ENDS -\n--------------------\n%s", KYEL, KNRM);
}
