/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:16:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 12:37:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_isprint(void)
{
	printf("---------------------------\n");
	printf("FT_ISPRINT:\n");
	printf("Ascii value 0 isprint return value: %i\n", ft_isprint(0));
	printf("Ascii value -1 isprint return value: %i\n", ft_isprint(-1));
	printf("Ascii value 127 isprint return value: %i\n", ft_isprint(127));
	printf("Ascii value 126 ('~') isprint return value: %i\n", ft_isprint(126));
	printf("Ascii value 32 (' ') isprint return value: %i\n", ft_isprint(32));
	printf("Char z isprint return value: %i\n", ft_isprint('z'));
	printf("Char @ isprint return value: %i\n", ft_isprint('@'));
	printf("---------------------------\n\n");
}
