/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:40:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/01 12:58:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_bzero(void)
{
	char	str[20] = "TestiString.";
	char	str2[5] = "\0\0\0\0\0";
	char	str3[5];
	char	str4[5] = "ABCDE";

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
	ft_bzero(str4, 0);
	printf("Str4 contains ABCDE, running bzero with length 0 and it is: %s\n", str4);
	printf("---------------------------\n\n");
}
