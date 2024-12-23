/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:41:28 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 15:41:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_itoa(void)
{
	char *itoa;

	itoa = ft_itoa(-2147483648);
	printf("---------------------------\n");
	printf("FT_ITOA:\n");
	printf("Digit: %li, string: %s\n", -2147483648, itoa);
	free(itoa);
	itoa = ft_itoa(0);
	printf("Digit: %i, string: %s\n", 0, itoa);
	free(itoa);
	itoa = ft_itoa(2147483647);
	printf("Digit: %i, string: %s\n", 2147483647, itoa);
	free(itoa);
	printf("---------------------------\n\n");
}
