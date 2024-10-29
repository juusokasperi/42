/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isascii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:16:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 12:34:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_isascii(void)
{
	printf("---------------------------\n");
	printf("FT_ISASCII:\n");
	printf("Ascii value 0 isascii return value: %i\n", ft_isascii(0));
	printf("Ascii value -1 isascii return value: %i\n", ft_isascii(-1));
	printf("Ascii value 127 isascii return value: %i\n", ft_isascii(127));
	printf("Char z isascii return value: %i\n", ft_isascii('z'));
	printf("Char @ isascii return value: %i\n", ft_isascii('@'));
	printf("---------------------------\n\n");
}
