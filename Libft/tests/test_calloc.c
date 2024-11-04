/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_calloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:03:31 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/01 17:38:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_calloc(void)
{
	printf("---------------------------\n");
	printf("FT_CALLOC:\n");
	char	*str;
	char	*ft_str;
	printf("Attempting to calloc 15 * sizeof(char)..\n");
	str = calloc(15, sizeof(char));
	ft_str = ft_calloc(15, sizeof(char));
	if (str && ft_str)
		printf("\tCalloc successful, comparing ft_str and str: \"%d\".\n", ft_memcmp(str, ft_str, 15));
	else
	{
		printf("\tCalloc failed.\n");
		return ;
	}
	free(str);
	free(ft_str);

	printf("Attempting to calloc 0 * sizeof(char)..\n");
	str = calloc(0, sizeof(char));
	ft_str = ft_calloc(0, sizeof(char));
	if (str && ft_str)
		printf("\tCalloc successful, comparing ft_str and str: \"%d\".\n", ft_memcmp(str, ft_str, 0));
	else
	{
		printf("\tCalloc failed.\n");
		return ;
	}
	free(str);

	printf("Attempting to calloc -10 * sizeof(char)..\n");
	str = calloc(-10, sizeof(char));
	ft_str = ft_calloc(-10, sizeof(char));

	if (str && ft_str)
		printf("\tCalloc successful, comparing ft_str and str: \"%d\".\n", ft_memcmp(str, ft_str, -10));
	else
	{
		printf("\tCalloc failed.\n");
		return ;
	}


	printf("---------------------------\n\n");

}
