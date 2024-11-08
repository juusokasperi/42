/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strnstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:51:10 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 12:00:36 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strnstr(void)
{
	char str[13] = "TestiString.";
	printf("---------------------------\n");
	printf("FT_STRNSTR:\n");

	printf("\"%s\" and \"ring\" to strnstr, length of 12\n", str);
	char *ptr = ft_strnstr(str, "ring", 12);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");

	printf("\"%s\" and \"ring\" to strnstr, length of 10\n", str);
	ptr = ft_strnstr(str, "ring", 10);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");

	printf("\"%s\" and \"ring\" to strnstr, length of 10\n", str);
	ptr = ft_strnstr(str, "ring", 12);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");

	printf("\"%s\" and \"ringy\" to strnstr, length of 12\n", str);
	ptr = ft_strnstr(str, "ringy", 12);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");
	char str2[] = "";

	printf("\"%s\" and \"ringy\" to strnstr, length of 12\n", str2);
	ptr = ft_strnstr(str2, "ringy", 12);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");

	printf("\"%s\" and \"\" to strnstr, length of 12\n", str);
	ptr = ft_strnstr(str, "", 12);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");

	printf("\"%s\" and \"String\" to strnstr, length of 6\n", str);
	ptr = ft_strnstr(str, "String", 6);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");

	printf("\"%s\" and \"String\" to strnstr, length of 0\n", str);
	ptr = ft_strnstr(str, "String", 0);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");

	printf("\"%s\" and \"String\" to strnstr, length of 5000\n", str);
	ptr = ft_strnstr(str, "String", 5000);
	if (ptr)
		printf("	Substring found: %s\n", ptr);
	else
		printf("	Substring not found\n");

	printf("\"%s\" and \"String\" to strnstr, length of -50\n", str);
	ptr = ft_strnstr(str, "String", -50);
	if (ptr)
		printf("	FT: Substring found: %s\n", ptr);
	else
		printf("	FT: Substring not found\n");
	ptr = strnstr(str, "String", -50);
	if (ptr)
		printf("	ORIG: Substring found: %s\n", ptr);
	else
		printf("	ORIG: Substring not found\n");

	printf("\"\" and \"\" to strnstr, length of 6\n");
	ptr = ft_strnstr("", "", 6);
	if (ptr)
		printf("	FT: Substring found: %s\n", ptr);
	else
		printf("	FT: Substring not found\n");
	ptr = strnstr("", "", 6);
	if (ptr)
		printf("	ORIG: Substring found: %s\n", ptr);
	else
		printf("	ORIG: Substring not found\n");
	printf("---------------------------\n\n");
}
