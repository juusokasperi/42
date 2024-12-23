/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:21:42 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 15:25:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strdup(void)
{
	char *str;
	char *str2;

	printf("---------------------------\n");
	printf("FT_STRDUP:\n");
	str = ft_strdup("String.");
	str2 = ft_strdup(str);
	printf("After strdup, str is \"%s\" and str2 is \"%s\"\n", str, str2);
	str2[0] = 'B';
	printf("Checking if altering str2 changes str.\n");
	printf("Str is \"%s\" and str2 is \"%s\"\n", str, str2);
	printf("---------------------------\n\n");

}
