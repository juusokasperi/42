/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:05:15 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 18:09:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strlen(char *str);

int	main(int argc, char **argv)
{
	if (argc != 2)
		printf("Usage: %s Strlen_To_Count\n", argv[0]);
	else
		printf("Length of %s is %i\n", argv[1], ft_strlen(argv[1]));
	return (0);
}
