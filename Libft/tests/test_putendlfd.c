/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putendlfd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:57:21 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 12:25:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_putendlfd(void)
{
	printf("---------------------------\n");
	printf("FT_PUTENDLFD:\n");
	printf("Str "" to stdout:\n");
	ft_putendl_fd("", 1);
	printf("Str \"Hello world\" to stdout:\n");
	ft_putendl_fd("Hello world", 1);
	printf("Str \"Hello world\" to stdin:\n");
	ft_putendl_fd("Hello world", 0);
	printf("Str \"Hello world\" to stderr:\n");
	ft_putendl_fd("Hello world", 2);
	printf("Str \"\tTerve\t\\0Esa\" to stdout:\n");
	ft_putendl_fd("\tTerve\t\0Esa", 1);
	printf("\n---------------------------\n\n");
}
