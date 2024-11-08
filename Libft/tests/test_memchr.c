/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:27:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 11:37:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_memchr(void)
{
	char memchrstr[12] = "TestiString.";

	printf("---------------------------\n");
	printf("FT_MEMCHR:\n");

	printf("Looking for \".\" from \"%s\" , length of 12\n", memchrstr);
	char *result = ft_memchr(memchrstr, '.', 12);
	if (result)
		printf("	Found at position: %ld\n", (char *)result - memchrstr);
	else
		printf("	Character not found\n");

	printf("Looking for \"S\" from \"%s\" , length of 12\n", memchrstr);
	result = ft_memchr(memchrstr, 'S', 12);
	if (result)
		printf("	Found at position: %ld\n", (char *)result - memchrstr);
	else
		printf("	Character not found\n");

	printf("Looking for \"Y\" from \"%s\" , length of 12\n", memchrstr);
	result = ft_memchr(memchrstr, 'Y', 12);
	if (result)
		printf("	Found at position: %ld\n", (char *)result - memchrstr);
	else
		printf("	Character not found\n");
	printf("---------------------------\n\n");
}
