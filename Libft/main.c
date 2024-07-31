/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:37:22 by jrinta-           #+#    #+#             */
/*   Updated: 2024/07/31 11:21:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	// Test strlen:
	printf("---------------------------\n");
	size_t i = ft_strlen("Test");
	printf("FT_STRLEN:\n");
	printf("Length of \"Test\" is %zu\n", i);
	printf("---------------------------\n\n");
	// Test memset:
	printf("---------------------------\n");
	char str[20] = "TestiString.";
	printf("FT_MEMSET:\n");
	printf("\"%s\" to memset with char '0' and length of 5\n", str);
	ft_memset(str, '0', 5);
	printf("After memset: \"%s\"\n", str);
	printf("---------------------------\n\n");
	// Test bzero:
	printf("---------------------------\n");
	printf("FT_BZERO:\n");
	printf("\"%s\" to bzero, length of 13\n", str);
	ft_bzero(str, 13);
	printf("After bzero: \"%s\"\n", str);
	printf("---------------------------\n\n");
	// Test memcpy:
	char str2[20] = "TestiString.";
	char str3[5];
	printf("---------------------------\n");
	printf("FT_MEMCPY:\n");
	printf("\"%s\" to memcpy, length of 5\n", str2);
	ft_memcpy(str3, str2, 5);
	printf("After memcpy: \"%s\"\n", str3);
	printf("---------------------------\n\n");
}
