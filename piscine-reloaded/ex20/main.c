/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:18:01 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 18:23:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char *ft_strdup(char *src);

int	main(void)
{
	char *str = "Testi String.";
	char *cpy;

	cpy = ft_strdup(str);
	if (cpy)
	{
		printf("Cpy is %s\n", cpy);
		free(cpy);
	}
	else
		printf("Malloc failed.\n");
	return (1);
}
