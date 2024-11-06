/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:27:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 19:41:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <bsd/string.h>

void	test_strrchr(void)
{
	char str[] = "Test String With Letter Y";
	char *ptr;

	printf("---------------------------\n");
	printf("FT_STRRCHR:\n");
	printf("Test string is: \"%s\"\n\n", str);

	ptr = ft_strrchr(str, 'Y');
	printf("FT: Looking for Y, ptr points to %s\n", ptr);
	ptr = strrchr(str, 'Y');
	printf("ORIG: Looking for Y, ptr points to %s\n\n", ptr);

	ptr = ft_strrchr(str, 'L');
	printf("FT: Looking for L, ptr points to %s\n", ptr);
	ptr = strrchr(str, 'L');
	printf("ORIG: Looking for L, ptr points to %s\n\n", ptr);


	ptr = ft_strrchr(str, 'r');
	printf("FT: Looking for r, ptr points to %s\n", ptr);
	ptr = strrchr(str, 'r');
	printf("ORIG: Looking for r, ptr points to %s\n\n", ptr);

	ptr = ft_strrchr(str, 'i');
	printf("FT: Looking for i, ptr points to %s\n", ptr);
	ptr = strrchr(str, 'i');
	printf("ORIG: Looking for i, ptr points to %s\n\n", ptr);

	ptr = ft_strrchr(str, '\0');
	printf("FT: Looking for '\\0', ptr points to %s\n", ptr);
	ptr = strrchr(str, '\0');
	printf("ORIG: Looking for '\\0', ptr points to %s\n\n", ptr);

	ptr = ft_strrchr(str, 'X');
	printf("FT: Looking for 'X', ptr points to %s\n", ptr);
	ptr = strrchr(str, 'X');
	printf("ORIG: Looking for 'X', ptr points to %s\n\n", ptr);

	ptr = ft_strrchr(str, 'T');
	printf("FT: Looking for 'T', ptr points to %s\n", ptr);
	ptr = strrchr(str, 'T');
	printf("ORIG: Looking for 'T', ptr points to %s\n\n", ptr);

	ptr = ft_strrchr("", 'Y');
	printf("FT: Looking for 'Y' from an empty string, ptr points to %s\n", ptr);
	ptr = strrchr("", 'Y');
	printf("ORIG: Looking for 'Y' from an empty string, ptr points to %s\n\n", ptr);

	ptr = ft_strrchr("Y", 'Y');
	printf("FT: Looking for 'Y' from a string with only that character, ptr points to %s\n", ptr);
	ptr = strrchr("Y", 'Y');
	printf("ORIG: Looking for 'Y' from a string with only that character, ptr points to %s\n\n", ptr);

	printf("---------------------------\n\n");
}
