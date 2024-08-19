/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:37:22 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 16:55:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	test_strlen(void)
{
	printf("---------------------------\n");
	printf("FT_STRLEN:\n");
	printf("Length of \"Test\" is %zu\n", ft_strlen("Test"));
	printf("Length of \"\" is %zu\n", ft_strlen(""));
	printf("---------------------------\n\n");
}

void	test_memset(void)
{
	printf("---------------------------\n");
	char str[20] = "TestiString.";
	printf("FT_MEMSET:\n");
	printf("\"%s\" to memset with char '0' and length of 5\n", str);
	ft_memset(str, '0', 5);
	printf("After memset: \"%s\"\n", str);
	printf("---------------------------\n\n");
}

void	test_bzero(void)
{
	char str[20] = "TestiString.";
	printf("---------------------------\n");
	printf("FT_BZERO:\n");
	printf("\"%s\" to bzero, length of 13\n", str);
	ft_bzero(str, 13);
	printf("After bzero: \"%s\"\n", str);
	printf("---------------------------\n\n");
}

void	test_memcpy(void)
{
	char str[20] = "TestiString.";
	char str2[5];
	printf("---------------------------\n");
	printf("FT_MEMCPY:\n");
	printf("\"%s\" to memcpy, length of 5\n", str);
	ft_memcpy(str, str2, 5);
	printf("After memcpy: \"%s\"\n", str2);
	printf("---------------------------\n\n");
}

void	test_strncmp(void)
{
	char strncmp1[12] = "TestiString.";
	char strncmp2[12] = "TestiBring.";
	printf("---------------------------\n");
	printf("FT_STRNCMP:\n");
	printf("\"%s\" and \"%s\" to strncmp, length of 5 and 10\n", strncmp1, strncmp2);
	printf("%i\n", ft_strncmp(strncmp1, strncmp2, 5));
	printf("%i\n", ft_strncmp(strncmp1, strncmp2, 10));
	printf("---------------------------\n\n");
}

void	test_memchr(void)
{
	char memchrstr[12] = "TestiString.";
	printf("---------------------------\n");
	printf("FT_MEMCHR:\n");
	printf("\"%s\" and \".\" to memchr, length of 12\n", memchrstr);
	void *result = ft_memchr(memchrstr, '.', 12);
	if (result)
		printf("Found at position: %ld\n", (char *)result - memchrstr);
	else
		printf("Character not found\n");
	printf("---------------------------\n\n");
}

void	test_strnstr(void)
{
	char str[12] = "TestiString.";
	printf("---------------------------\n");
	printf("FT_STRNSTR:\n");
	printf("\"%s\" and \"ring\" to strnstr, length of 12\n", str);
	char *ptr = ft_strnstr(str, "ring", 12);
	if (ptr)
		printf("Substring found: %s\n", ptr);
	else
		printf("Substring not found\n");
	printf("---------------------------\n\n");
}

void	test_substr(void)
{
	char str[12] = "TestiString.";
	char *substr = ft_substr(str, 5, 6);
	printf("---------------------------\n");
	printf("FT_SUBSTR:\n");
	printf("\"%s\" to substr, start index 5, length 6\n", str);
	printf("\"%s\" substr\n", substr);
	printf("---------------------------\n\n");
	free(substr);
}

void	test_strtrim(void)
{
	char *str = "abababCS2 kelpaa pelata baaban vierelläbabababa";
	char *str_trimmed = ft_strtrim(str, "ab");
	printf("---------------------------\n");
	printf("FT_STRTRIM:\n");
	printf("\"%s\" to strtrim with charset \"ab\"\n", str);
	printf("\"%s\"\n", str_trimmed);
	printf("---------------------------\n\n");
	free(str_trimmed);
}

void	test_split(void)
{
	int	i;

	i = 0;
	printf("---------------------------\n");
	printf("FT_SPLIT:\n");
	char **array = ft_split("BTestiBStringBHuomenta", 'B');
	printf("Test1: \"BTestiBStringBHuomenta\", 'B'\n");
	while (array[i])
	{
		printf("%s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
	i = 0;
	printf("\n");
	array = ft_split("Testi!Stringi!Homma!", '!');
	printf("Test2: \"Testi!Stringi!Homma!\", '!'\n");
	while (array[i])
	{
		printf("%s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
		i = 0;
	printf("\n");
	array = ft_split("BBBBBB", 'B');
	printf("Test3: \"BBBBBB\", 'B'\n");
	while (array[i])
	{
		printf("%s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
	printf("---------------------------\n\n");
}

void	test_itoa(void)
{
	char *itoa;

	itoa = ft_itoa(-2147483648);
	printf("---------------------------\n");
	printf("FT_ITOA:\n");
	printf("Digit: %li, string: %s\n", -2147483648, itoa);
	free(itoa);
	itoa = ft_itoa(0);
	printf("Digit: %i, string: %s\n", 0, itoa);
	free(itoa);
	itoa = ft_itoa(2147483647);
	printf("Digit: %i, string: %s\n", 2147483647, itoa);
	free(itoa);
	printf("---------------------------\n\n");
}

void	test_putnbrfd(void)
{
	printf("---------------------------\n");
	printf("FT_PUTNBR_FD:\n");
	ft_putnbr_fd(-2147483648, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-50, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(0, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(50, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(2147483647, 1);
	write(1, "\n", 1);
	printf("---------------------------\n\n");
}

int	main(void)
{
	test_strlen();
	test_memset();
	test_bzero();
	test_memcpy();
	test_strncmp();
	test_memchr();
	test_strnstr();
	test_substr();
	test_strtrim();
	test_split();
	test_itoa();
	test_putnbrfd();
}
