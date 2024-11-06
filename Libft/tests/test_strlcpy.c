/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:59:52 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 19:26:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <bsd/string.h>

void	test_strlcpy(void)
{
	char src[6] = "Testi";
	char dest[6] = "";
	printf("---------------------------\n");
	printf("FT_STRLCPY:\n");
	printf("Src is \"%s\" and dest is \"%s\". Running strlcpy, length of 6.\n", src, dest);
	ft_strlcpy(dest, src, 6);
	printf("After strlcpy dest is: \"%s\" and src is \"%s\"\n\n", dest, src);

	strlcpy(dest, "", 6);
	long i = strlcpy(dest, "Testi", 6);
	printf("ORIG: \"\" and \"Testi\", size 6, dest is: %s, ret value: %ld\n", dest, i);
	ft_strlcpy(dest, "", 6);
	i = ft_strlcpy(dest, "Testi", 6);
	printf("FT: \"\" and \"Testi\", size 6, dest is: %s, ret value: %ld\n\n", dest, i);

	strlcpy(dest, "", 6);
	i = strlcpy(dest, "", 0);
	printf("ORIG: \"\" and \"\", size 0, dest is: %s, ret value: %ld\n", dest, i);
	ft_strlcpy(dest, "", 6);
	i = ft_strlcpy(dest, "", 0);
	printf("FT: \"\" and \"\", size 0, dest is: %s, ret value: %ld\n\n", dest, i);

	strlcpy(dest, "", 6);
	i = strlcpy(dest, "Testi", 4);
	printf("ORIG: \"\" and \"Testi\", size 4, dest is: %s, ret value: %ld\n", dest, i);
	ft_strlcpy(dest, "", 6);
	i = ft_strlcpy(dest, "Testi", 4);
	printf("FT: \"\" and \"Testi\", size 4, dest is: %s, ret value: %ld\n\n", dest, i);
/*
	printf("\nThese should segfault:\n");
	printf("ORIG: \"\" and \"Testi\", ret value: %ld\n", strlcpy(dest, NULL, 6));
	printf("FT: \"\" and \"Testi\", ret value: %ld\n", ft_strlcpy(dest, NULL, 6));
	printf("ORIG: \"\" and \"Testi\", ret value: %ld\n", strlcpy(NULL, NULL, 6));
	printf("FT: \"\" and \"Testi\", ret value: %ld\n", ft_strlcpy(NULL, NULL, 6));
	printf("---------------------------\n\n");
*/
}
