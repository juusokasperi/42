/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_toupper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:20:34 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:25:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_toupper(void)
{
	char	str[] = "Str1ng W/ L0w3r and upp3r c453 plu5 d1g175.";
	int		i;

	printf("---------------------------\n");
	printf("FT_TOUPPER:\n");
	printf("Before: \"%s\"\n", str);
	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	printf("After: \"%s\"\n", str);
	printf("---------------------------\n\n");
}
