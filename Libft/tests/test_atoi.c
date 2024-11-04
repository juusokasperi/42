/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:56:23 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/01 12:57:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_atoi(void)
{
	printf("---------------------------\n");
	printf("FT_ATOI:\n");
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       -0", ft_atoi("       -0"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       +0", ft_atoi("       +0"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       0BX", ft_atoi("       0BX"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       -2147483648", ft_atoi("       -2147483648"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       2147483647", ft_atoi("       2147483647"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       2147483648", ft_atoi("       2147483648"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       +500X40", ft_atoi("       +500X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       +-500X40", ft_atoi("       +-500X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       +5Y500X40", ft_atoi("       +5Y500X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       -50B0X40", ft_atoi("       -50B0X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       B-50B0X40", ft_atoi("       B-50B0X40"));
	printf("---------------------------\n\n");

}
