/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 16:12:19 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

void	test_str(void)
{
	printf("--------------------\n-  TESTING STRING  -\n--------------------\n");
	char *str = "Test String";
	printf("PF: %s\n", str);
	ft_printf("FT: %s\n\n", str);

	printf("Width flag:\n");
//	printf("PF: x%020s\n", str);
//	ft_printf("FT: x%020s\n", str);
	printf("PF: %5s\n", str);
	ft_printf("FT: %5s\n\n", str);

	printf("Left-align\n");
	printf("PF: %-20sx\n", str);
	ft_printf("FT: %-20sx\n\n", str);

	printf("Precision 0\n");
	printf("PF: %.0s\n", str);
    ft_printf("FT: %.0s\n\n", str);

	printf("Other precision and combinations\n");
	printf("PF: %.5s\n", str);
	ft_printf("FT: %.5s\n", str);
	printf("PF: %.50s\n", str);
	ft_printf("FT: %.50s\n", str);
	printf("PF: %20.10s\n", str);
	ft_printf("FT: %20.10s\n", str);
	printf("PF: %-20.10sx\n", str);
	ft_printf("FT: %-20.10sx\n", str);
	printf("--------------------\n- STRING TEST ENDS -\n--------------------\n");
}
