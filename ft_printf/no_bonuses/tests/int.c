/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/15 16:43:58 by jrinta-          ###   ########.fr       */
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
	ret = printf("PF: %i\n", 0);
	ret_ft = ft_printf("FT: %i\n", 0);
	cmp(ret, ret_ft);
	ret = printf("PF: %d\n", 2147483650);
	ret_ft = ft_printf("FT: %d\n", 2147483650);
	cmp(ret, ret_ft);
	printf("%s--------------------\n- INT  TEST ENDS  -\n--------------------\n%s", KYEL, KNRM);
}
