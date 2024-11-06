/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strncmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:34:38 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 19:27:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <bsd/string.h>

void	test_strncmp(void)
{
	char strncmp1[20] = "TestiString.";
	char strncmp2[20] = "TestiBring.";
	printf("---------------------------\n");
	printf("FT_STRNCMP:\n");
	printf("\"%s\" and \"%s\" to strncmp, length of 5 and 10\n", strncmp1, strncmp2);
	printf("ORIG: %i\n", strncmp(strncmp1, strncmp2, 5));
	printf("FT: %i\n", ft_strncmp(strncmp1, strncmp2, 5));
	printf("ORIG: %i\n", strncmp(strncmp1, strncmp2, 10));
	printf("FT: %i\n", ft_strncmp(strncmp1, strncmp2, 10));
	printf("\"%s\" and \"%s\" to strncmp, length of 10 and 0\n", "ABC", "ABX");
	printf("ORIG: %i\n", strncmp("ABC", "ABX", 10));
	printf("FT: %i\n", ft_strncmp("ABC", "ABX", 10));
	printf("ORIG: %i\n", strncmp("ABC", "ABX", 0));
	printf("FT: %i\n", ft_strncmp("ABC", "ABX", 0));
	printf("\"%s\" and \"%s\" to strncmp, length of 3 and 10\n", "ABC", "AB");
	printf("ORIG: %i\n", strncmp("ABC", "AB", 3));
	printf("FT: %i\n", ft_strncmp("ABC", "AB", 3));
	printf("ORIG: %i\n", strncmp("ABC", "AB", 10));
	printf("FT: %i\n", ft_strncmp("ABC", "AB", 10));

	printf("\"%s\" and \"%s\" to strncmp, length of 3 and 10\n", "AB", "ABC");
	printf("ORIG: %i\n", strncmp("AB", "ABC", 3));
	printf("FT: %i\n", ft_strncmp("AB", "ABC", 3));
	printf("ORIG: %i\n", strncmp("AB", "ABC", 10));
	printf("FT: %i\n", ft_strncmp("AB", "ABC", 10));
	printf("---------------------------\n\n");
}
