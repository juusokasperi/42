/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:40:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 13:07:59 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_bzero(void)
{
	char	str[20] = "TestiString.";
	char	str2[5] = "\0\0\0\0\0";
	char	str3[5];

	printf("---------------------------\n");
	printf("FT_BZERO:\n");
	printf("\"%s\" to bzero, length of 5\n", str);
	ft_bzero(str, 5);
	printf("After bzero: \"%s\"\n", str);
	printf("Printing str from str + 5 onwards (String. should still be there)\n");
	printf("\"%s\"\n", str + 5);
	ft_bzero(str3, 5);
	printf("Str2[5] is filled with \"\\0\\0\\0\\0\\0\". ");
	printf("Running ft_bzero(str3, 5) and ft_memcmp(str2, str3, 5).\n");
	printf("Return value is %d\n", ft_memcmp(str2, str3, 5));
	printf("---------------------------\n\n");
}
