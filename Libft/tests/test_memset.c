/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:38:05 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 12:39:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
