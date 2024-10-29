/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:41:10 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 12:59:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_memcpy(void)
{
	char dest[10] = "Testi";
	char src[10] = "Roflmao";
	printf("---------------------------\n");
	printf("FT_MEMCPY:\n");
	printf("Src is \"%s\" and dest is \"%s\". Running memcpy, length of 7.\n", src, dest);
	ft_memcpy(dest, src, 7);
	printf("After memcpy dest is: \"%s\" and src is \"%s\"\n", dest, src);
	printf("---------------------------\n\n");
}
