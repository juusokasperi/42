/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:40:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 12:40:36 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_bzero(void)
{
	char str[20] = "TestiString.";
	printf("---------------------------\n");
	printf("FT_BZERO:\n");
	printf("\"%s\" to bzero, length of 13\n", str);
	ft_bzero(str, 13);
	printf("After bzero: \"%s\"\n", str);
	printf("---------------------------\n\n");
}
