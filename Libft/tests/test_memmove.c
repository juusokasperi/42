/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memmove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:49:58 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 12:53:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_memmove(void)
{
	char dest[20] = "TestiString.";
	char src[20] = "TestStringy.";
	printf("---------------------------\n");
	printf("FT_MEMMOVE:\n");
	printf("Before memmove dest is %s and src is %s\n", dest, src);
	ft_memmove(dest, src, 20);
	printf("After memmove dest is %s and src is %s\n", dest, src);
	printf("---------------------------\n\n");
}
