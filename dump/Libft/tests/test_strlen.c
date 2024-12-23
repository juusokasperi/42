/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:38:05 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 10:15:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strlen(void)
{
	printf("---------------------------\n");
	printf("FT_STRLEN:\n");
	printf("Length of \"Test\" is %zu\n", ft_strlen("Test"));
	printf("Length of \"\" is %zu\n", ft_strlen(""));
	printf("Length of \"\\t\\0\" is %zu\n", ft_strlen("\t\0"));
	printf("---------------------------\n\n");
}
