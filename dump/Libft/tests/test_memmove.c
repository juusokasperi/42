/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memmove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:49:58 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 11:33:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <string.h>

void	test_memmove(void)
{
	char dest[100] = "TestiString.";
	char m_dest[100] = "TestiString.";
	char src[20] = "Jeps.";
	printf("---------------------------\n");
	printf("FT_MEMMOVE:\n");
	printf("Before memmove dest is %s and src is %s\n\n", dest, src);
	ft_memmove(dest, src, 5);
	memmove(m_dest, src, 5);
	printf("After ft_memmove dest is %s and src is %s\n", dest, src);
	printf("After memmove dest is %s and src is %s\n\n", m_dest, src);

	ft_memmove(dest, dest + 5, 5);
	memmove(m_dest, m_dest + 5, 5);
	printf("After ft_memmove dest + 5 to dest, dest is %s\n", dest);
	printf("After memmove dest + 5 to dest, dest is %s\n\n", m_dest);

	ft_memmove(dest + 8, dest, 5);
	memmove(m_dest + 8, m_dest, 5);
	printf("After ft_memmove dest to dest + 8, dest is %s\n", dest);
	printf("After memmove dest to dest + 8, dest is %s\n", m_dest);

	printf("---------------------------\n\n");
}
