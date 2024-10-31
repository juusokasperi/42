/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:38:05 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 10:28:56 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_memset(void)
{
	char	str[20] = "TestiString.";
	char	str2[5];
	int		i;

	printf("---------------------------\n");
	printf("FT_MEMSET:\n");
	printf("\"%s\" to memset with char '0' and length of 5\n", str);
	printf("Empty str2[5] to memset with char 'B' and length 5\n");
	ft_memset(str, '0', 5);
	ft_memset(str2, 'B', 5);
	printf("After memset: \"%s\"\n", str);
	printf("After memset: ");
	i = 0;
	while (i < 5)
		printf("%c", str2[i++]);
	printf("\n");
	printf("---------------------------\n\n");
}
