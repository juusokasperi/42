/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:59:52 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 21:50:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strlcat(void)
{
	char	src[6] = "Testi";
	char	dest[20] = "String ";
	char	s_dest[20] = "String ";
	char	dest2[10];
	char	s_dest2[10];
	char	dest3[12] = "Kissa\0Koira";
	char	s_dest3[12] = "Kissa\0Koira";

	printf("---------------------------\n");
	printf("FT_STRLCAT:\n");
	printf("FT Before: Src is %s, dest is %s\n", src, dest);
	printf("STRLCAT Before: Src is %s, dest is %s\n\n", src, s_dest);

	ft_strlcat(dest, src, 20);
	strlcat(s_dest, src, 20);
	printf("FT After: Src is %s, dest is %s\n", src, dest);
	printf("STRLCAT After: Src is %s, dest is %s\n\n", src, s_dest);

	ft_strlcat(dest2, "0123456789", 10);
	strlcat(s_dest2, "0123456789", 10);
	printf("FT: Src is %s, dest[10], len 10 is %s\n", "0123456789", dest2);
	printf("STRLCAT: Src is %s, dest[10], len 10 is %s\n\n", "0123456789", s_dest2);

	ft_strlcat(dest3, "0123456789", 0);
	strlcat(s_dest3, "0123456789", 0);
	printf("FT: Src is %s, dest[10], len 10 is %s\n", "0123456789", dest3);
	printf("STRLCAT: Src is %s, dest[10], len 10 is %s\n", "0123456789", s_dest3);
	printf("---------------------------\n\n");
}
