/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 10:54:13 by jrinta-          ###   ########.fr       */
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
	ret =  printf("%c%c%c\n", 'a', '\t', 'b');
	ret_ft =  ft_printf("%c%c%c\n", 'a', '\t', 'b');
	cmp(ret, ret_ft);
	printf("%s--------------------\n-  CHAR TEST ENDS  -\n--------------------%s\n",
		KYEL, KNRM);
}
