/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:16:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 10:11:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_isalpha(void)
{
	printf("---------------------------\n");
	printf("FT_ISALPHA:\n");
	printf("Char A isalpha return value: %i\n", ft_isalpha('A'));
	printf("Char Z isalpha return value: %i\n", ft_isalpha('Z'));
	printf("Char a isalpha return value: %i\n", ft_isalpha('a'));
	printf("Char z isalpha return value: %i\n", ft_isalpha('z'));
	printf("Char @ isalpha return value: %i\n", ft_isalpha('@'));
	printf("Char \\0 isalpha return value: %i\n", ft_isalpha('\0'));
	printf("Char \\t isalpha return value: %i\n", ft_isalpha('\t'));
	printf("---------------------------\n\n");
}
