/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strnstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:51:10 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 19:36:33 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <bsd/string.h>

void	test_strnstr(void)
{
	char str[12] = "TestiString.";
	printf("---------------------------\n");
	printf("FT_STRNSTR:\n");
	printf("\"%s\" and \"ring\" to strnstr, length of 12\n", str);
	char *ptr = ft_strnstr(str, "ring", 12);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");
	printf("\"%s\" and \"ringy\" to strnstr, length of 12\n", str);
	char *ptr2 = ft_strnstr(str, "ringy", 12);
	if (ptr2)
		printf("	Substring found: %s\n", ptr2);
	else
		printf("	Substring not found\n");
	char str2[] = "";
	printf("\"%s\" and \"ringy\" to strnstr, length of 12\n", str2);
	char *ptr3 = ft_strnstr(str2, "ringy", 12);
	if (ptr3)
		printf("	Substring found: %s\n", ptr3);
	else
		printf("	Substring not found\n");
	printf("\"%s\" and \"\" to strnstr, length of 12\n", str);
	char *ptr4 = ft_strnstr(str, "", 12);
	if (ptr4)
		printf("	Substring found: %s\n", ptr4);
	else
		printf("	Substring not found\n");
	printf("\"%s\" and \"String\" to strnstr, length of 6\n", str);
	char *ptr5 = ft_strnstr(str, "String", 6);
	if (ptr5)
		printf("	Substring found: %s\n", ptr5);
	else
		printf("	Substring not found\n");
	printf("---------------------------\n\n");
}
