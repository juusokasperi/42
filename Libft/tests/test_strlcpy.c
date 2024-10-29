/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:59:52 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:02:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strlcpy(void)
{
	char src[6] = "Testi";
	char dest[6] = "";
	printf("---------------------------\n");
	printf("FT_STRLCPY:\n");
	printf("Src is \"%s\" and dest is \"%s\". Running strlcpy, length of 6.\n", src, dest);
	ft_strlcpy(dest, src, 6);
	printf("After strlcpy dest is: \"%s\" and src is \"%s\"\n", dest, src);
	printf("---------------------------\n\n");
}
