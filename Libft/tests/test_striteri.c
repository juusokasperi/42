/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_striteri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:42:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 16:04:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	capitalize_c(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}


void	test_striteri(void)
{
	char	str[] = "testattava string 1234.";

	printf("---------------------------\n");
	printf("FT_STRITERI:\n");
	printf("Before: Str is %s\n", str);
	ft_striteri(str, capitalize_c);
	printf("After: Str is %s\n", str);
	printf("---------------------------\n\n");
}
