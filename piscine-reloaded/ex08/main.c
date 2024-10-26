/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:46:07 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 14:49:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	ft_is_negative(int n);

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		printf("Usage: %s INTEGER\n", argv[0]);
		return (1);
	}
	i = atoi(argv[1]);
	ft_is_negative(i);
	return (0);
}
