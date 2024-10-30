/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_calloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:03:31 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/30 17:03:27 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_calloc(void)
{
	printf("---------------------------\n");
	printf("FT_CALLOC:\n");
	char	*str;
	printf("Attempting to calloc 15 * sizeof(char)..\n");
	str = calloc(15, sizeof(char));
	if (str)
		printf("\tCalloc successful.\n");
	else
	{
		printf("\tCalloc failed.\n");
		return ;
	}

	printf("Attempting to calloc 0 * sizeof(char)..\n");
	str = calloc(0, sizeof(char));
	if (str)
		printf("\tCalloc successful.\n");
	else
	{
		printf("\tCalloc failed.\n");
		return ;
	}

	printf("---------------------------\n\n");

}
