/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/22 16:55:10 by jrinta-          ###   ########.fr       */
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

	printf("%s--------------------\nUnprintables\n%s", KCYN, KNRM);
	ret = printf("PF: \001\002\007\v\010\f\r\n");
	ret_ft = ft_printf("FT: \001\002\007\v\010\f\r\n");
	cmp(ret, ret_ft);
	printf("%s--------------------\n- STRING TEST ENDS -\n--------------------\n%s", KYEL, KNRM);
}
