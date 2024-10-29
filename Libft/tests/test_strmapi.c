/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strmapi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:42:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 16:00:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static char	capitalize_c(unsigned int i, char c)
{
	(void)i;
	return ft_toupper(c);
}


void	test_strmapi(void)
{
	char	*str = "testattava string 1234.";
	char	*str2;

	printf("---------------------------\n");
	printf("FT_STRMAPI:\n");
	str2 = ft_strmapi(str, capitalize_c);
	printf("Str is %s and str2 is %s\n", str, str2);
	printf("---------------------------\n\n");
}
