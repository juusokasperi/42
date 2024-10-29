/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:44:49 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:52:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_memcmp(void)
{
	char s1[10] = "Test\0ABC";
	char s2[10] = "Test\0BCD";
	printf("---------------------------\n");
	printf("FT_MEMCMP:\n");
	printf("Comparing \"Test\\0ABC\" and \"Test\\0BCD\" with memcmp.\n");
	printf("Comparing first 5 characters, return value: %i\n", ft_memcmp(s1, s2, 5));
	printf("Comparing first 8 characters, return value: %i\n", ft_memcmp(s1, s2, 8));
	printf("---------------------------\n\n");
}
