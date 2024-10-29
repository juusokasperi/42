/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_substr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:29:07 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 15:35:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_substr(void)
{
	char str[12] = "TestiString.";
	char *substr = ft_substr(str, 5, 6);
	printf("---------------------------\n");
	printf("FT_SUBSTR:\n");
	printf("\"%s\" to substr, start index 5, length 6\n", str);
	printf("\"%s\" substr\n", substr);
	printf("---------------------------\n\n");
	free(substr);
}
