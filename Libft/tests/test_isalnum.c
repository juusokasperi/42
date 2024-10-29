/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:16:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 12:31:17 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_isalnum(void)
{
	printf("---------------------------\n");
	printf("FT_ISALNUM:\n");
	printf("Char A isalnum return value: %i\n", ft_isalnum('A'));
	printf("Char Z isalnum return value: %i\n", ft_isalnum('Z'));
	printf("Char a isalnum return value: %i\n", ft_isalnum('a'));
	printf("Char z isalnum return value: %i\n", ft_isalnum('z'));
	printf("Char @ isalnum return value: %i\n", ft_isalnum('@'));
	printf("Char 0 isalnum return value: %i\n", ft_isalnum('0'));
	printf("Char 9 isalnum return value: %i\n", ft_isalnum('9'));
	printf("---------------------------\n\n");
}
