/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/14 13:29:20 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_char(void)
{
	int ret;
	int ret_ft;
	printf("%s--------------------\n-   TESTING CHAR   -\n--------------------%s\n\n",
		KYEL, KNRM);
	char c = 'c';
	ret = printf("PF: %c\n", c);
	ret_ft = ft_printf("FT: %c\n", c);
	cmp(ret, ret_ft);

	printf("%s--------------------\nWidth flag:\n%s", KBLU, KNRM);
	ret = printf("PF: x%20c\n", c);
	ret_ft = ft_printf("FT: x%20c\n", c);
	cmp(ret, ret_ft);
	ret = printf("PF: x%5c\n", c);
	ret_ft = ft_printf("FT: x%5c\n", c);
	cmp(ret, ret_ft);

	printf("%s--------------------\nLeft-align%s\n", KBLU, KNRM);
	ret = printf(" %-1c %-2c %-3c ", '0', 0, '1');
	ret_ft = ft_printf(" %-1c %-2c %-3c ", '0', 0, '1');
	cmp(ret, ret_ft);

	ret = printf(" %-1c %-2c %-3c ", '2', '1', 0);
	ret_ft = ft_printf(" %-1c %-2c %-3c ", '2', '1', 0);
	cmp(ret, ret_ft);

	ret = printf("PF: %-20cx\n", c);
	ret_ft = ft_printf("FT: %-20cx\n", c);
	cmp(ret, ret_ft);

	printf("%s--------------------\nFlag 0\n%s", KBLU, KNRM);
	ret = printf("PF: %0cx\n", c);
	ret_ft = ft_printf("FT: %0cx\n", c);
	cmp(ret, ret_ft);
	printf("%s--------------------\n-  CHAR TEST ENDS  -\n--------------------%s\n",
		KYEL, KNRM);
}
