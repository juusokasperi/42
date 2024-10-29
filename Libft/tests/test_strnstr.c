/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strnstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:51:10 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:52:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
	printf("---------------------------\n\n");
}
