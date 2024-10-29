/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isdigit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:16:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 12:30:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_isdigit(void)
{
	printf("---------------------------\n");
	printf("FT_ISDIGIT:\n");
	printf("Char 0 isdigit return value: %i\n", ft_isdigit('0'));
	printf("Char 9 isdigit return value: %i\n", ft_isdigit('9'));
	printf("Char a isdigit return value: %i\n", ft_isdigit('a'));
	printf("Char @ isdigit return value: %i\n", ft_isdigit('@'));
	printf("---------------------------\n\n");
}
