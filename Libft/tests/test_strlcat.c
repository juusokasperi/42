/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:59:52 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 16:22:06 by jrinta-          ###   ########.fr       */
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
	printf("STRLCAT Before: Src is %s, dest is %s\n", src, s_dest);
	ft_strlcat(dest, src, 20);
	strlcat(s_dest, src, 20);
	printf("FT After: Src is %s, dest is %s\n", src, dest);
	printf("STRLCAT After: Src is %s, dest is %s\n\n", src, s_dest);

	ft_strlcat(dest2, "0123456789", 10);
	strlcat(s_dest2, "0123456789", 10);
	printf("FT: Src is %s, dest[10] is empty, len 10 is %s\n", "0123456789", dest2);
	printf("STRLCAT: Src is %s, dest[10] is empty, len 10 is %s\n\n", "0123456789", s_dest2);

	ft_strlcat(dest3, "0123456789", 0);
	strlcat(s_dest3, "0123456789", 0);
	printf("FT: Src is %s, dest[12] is \"Kissa\\0Koira\", len 10 is %s\n", "0123456789", dest3);
	printf("STRLCAT: Src is %s, dest[12] is \"Kissa\\0Koira\", len 10 is %s\n", "0123456789", s_dest3);

	char b[15] = "nyan !";
	printf("ORIG: Src is %s, sze 0, dest null pointer: %zu\n", strlcat(((void*)0), b, 0));
	printf("FT: Src is %s, sze 0, dest null pointer: %zu\n", ft_strlcat(((void*)0), b, 0));
//	These are supposed to segfault:
//	printf("ORIG: Src is %s, sze 10, dest null pointer: %zu\n", b, strlcat(((void*)0), b, 10));
//	printf("FT: Src is %s, sze 10, dest null pointer: %zu\n", b, ft_strlcat(((void*)0), b, 10));
//	printf("ORIG: Src is null ptr, sze 0, dest %s: %zu\n", b, strlcat(b, ((void*)0), 0));
//	printf("FT: Src is null ptr, sze 0, dest %s: %zu\n", b, ft_strlcat(b, ((void*)0), 0));
	printf("---------------------------\n\n");
}
