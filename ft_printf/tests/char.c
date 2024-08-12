/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/12 16:22:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	test_char(void)
{
	printf("--------------------\n-   TESTING CHAR   -\n--------------------\n");
	char c = 'c';
	printf("PF: %c\n", c);
	ft_printf("FT: %c\n\n", c);

	printf("Width flag:\n");
	printf("PF: x%20c\n", c);
	ft_printf("FT: x%20c\n", c);
	printf("PF: x%5c\n", c);
	ft_printf("FT: x%5c\n\n", c);

	printf("Left-align\n");
	printf("PF: %-20cx\n", c);
	ft_printf("FT: %-20cx\n", c);
	printf("--------------------\n-  CHAR TEST ENDS  -\n--------------------\n");
}
