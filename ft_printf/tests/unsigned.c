/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/15 16:44:47 by jrinta-          ###   ########.fr       */
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

	ret = printf("PF: %u\n", -2147483648);
	ret_ft = ft_printf("FT: %u\n", -2147483648);
	cmp(ret, ret_ft);

	ret = printf("PF: %u\n", 0);
	ret_ft = ft_printf("FT: %u\n", 0);
	cmp(ret, ret_ft);

	printf("%s--------------------\n- UNSIGN TEST ENDS -\n--------------------\n%s", KYEL, KNRM);
}
