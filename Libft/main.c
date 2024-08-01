/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:37:22 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/01 12:06:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	char substr[6] = ft_substr(str, 5, 6);
	printf("---------------------------\n");
	printf("FT_SUBSTR:\n");
	printf("\"%s\" to substr, start index 5, length 6\n", str);
	printf("\"%s\" substr\n", substr);
	printf("---------------------------\n\n");
	free(substr);
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
}
