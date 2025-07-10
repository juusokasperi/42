/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/22 16:55:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_ptr(void)
{
	int ret;
	int ret_ft;
	int i = 500;
	void	*p = NULL;
	void	*p2 = (void*)0x1234567890ABCDEF;
	printf("%s--------------------\n- TESTING PTR -\n--------------------%s\n\n", KYEL, KNRM);
	ret = printf("PF: %p\n", &i);
	ret_ft = ft_printf("FT: %p\n", &i);
	cmp(ret, ret_ft);
	ret = printf("PF: %p\n", p);
	ret_ft = ft_printf("FT: %p\n", p);
	cmp(ret, ret_ft);

	printf("%s-------------------\nTest w 64-bit ptr%s\n", KCYN, KNRM);
	ret = printf("PF: %p\n", p2);
	ret_ft = ft_printf("FT: %p\n", p2);
	cmp(ret, ret_ft);
	printf("%s--------------------\n-  PTR  TEST  ENDS -\n--------------------%s\n", KYEL, KNRM);
}
