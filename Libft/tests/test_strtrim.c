/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:36:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 15:36:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strtrim(void)
{
	char *str = "abababCS2 kelpaa pelata baaban vierelläbabababa";
	char *str_trimmed = ft_strtrim(str, "ab");
	printf("---------------------------\n");
	printf("FT_STRTRIM:\n");
	printf("\"%s\" to strtrim with charset \"ab\"\n", str);
	printf("\"%s\"\n", str_trimmed);
	printf("---------------------------\n\n");
	free(str_trimmed);
}
