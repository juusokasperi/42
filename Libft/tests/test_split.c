/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:39:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 15:39:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_split(void)
{
	int	i;

	i = 0;
	printf("---------------------------\n");
	printf("FT_SPLIT:\n");
	char **array = ft_split("BTestiBStringBHuomenta", 'B');
	printf("Test1: \"BTestiBStringBHuomenta\", 'B'\n");
	while (array[i])
	{
		printf("%s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
	i = 0;
	printf("\n");
	array = ft_split("Testi!Stringi!Homma!", '!');
	printf("Test2: \"Testi!Stringi!Homma!\", '!'\n");
	while (array[i])
	{
		printf("%s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
		i = 0;
	printf("\n");
	array = ft_split("BBBBBB", 'B');
	printf("Test3: \"BBBBBB\", 'B'\n");
	while (array[i])
	{
		printf("%s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
	printf("---------------------------\n\n");
}
