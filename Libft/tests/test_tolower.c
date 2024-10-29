/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tolower.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:20:34 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:25:59 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_tolower(void)
{
	char	str[] = "STR1ng W/ L0W3r ANd uPP3r C453 plu5 D1g175.";
	int		i;

	printf("---------------------------\n");
	printf("FT_TOLOWER:\n");
	printf("Before: \"%s\"\n", str);
	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	printf("After: \"%s\"\n", str);
	printf("---------------------------\n\n");
}
