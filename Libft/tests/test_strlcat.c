/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:59:52 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:18:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strlcat(void)
{
	char src[6] = "Testi";
	char dest[20] = "String ";
	printf("---------------------------\n");
	printf("FT_STRLCAT:\n");
	printf("Before: Src is %s, dest is %s\n", src, dest);
	ft_strlcat(dest, src, 20);
	printf("After: Src is %s, dest is %s\n", src, dest);
	printf("---------------------------\n\n");
}
