/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:56:23 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/05 15:40:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdlib.h>

void	test_atoi(void)
{
	printf("LONG_MAX is: %li\nLONG_MIN is: %li\n", LONG_MAX, LONG_MIN);
	printf("---------------------------\n");
	printf("FT_ATOI:\n");
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       -0", ft_atoi("       -0"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       +0", ft_atoi("       +0"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       0BX", ft_atoi("       0BX"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       -2147483648", ft_atoi("       -2147483648"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       2147483647", ft_atoi("       2147483647"));

	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       +500X40", ft_atoi("       +500X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       +-500X40", ft_atoi("       +-500X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       +5Y500X40", ft_atoi("       +5Y500X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       -50B0X40", ft_atoi("       -50B0X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       B-50B0X40", ft_atoi("       B-50B0X40"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n", "       B-50B0X40", ft_atoi("       B-50B0X40"));
	printf("Sending \"%s\" to ft_atoi, result is \"%i\"\n", "       2147483648", ft_atoi("       2147483648"));
	printf("Sending \"%s\" to atoi, result is \"%i\"\n\n", "       2147483648", atoi("       2147483648"));

	printf("Regular atoi with long min: %i\n", atoi("-9223372036854775808"));
	printf("FT atoi with long min: %i\n\n", ft_atoi("-9223372036854775808"));
	printf("Regular atoi with long max: %i\n", atoi("9223372036854775807"));
	printf("FT atoi with long max: %i\n\n", ft_atoi("9223372036854775807"));
	printf("Regular atoi with long max - 1: %i\n", atoi("9223372036854775806"));
	printf("FT atoi with long max - 1: %i\n\n", ft_atoi("9223372036854775806"));
	printf("Regular atoi with long max + 1: %i\n", atoi("9223372036854775808"));
	printf("FT atoi with long max + 1: %i\n\n", ft_atoi("9223372036854775808"));
	printf("Regular atoi with long max + 1000: %i\n", atoi("9223372036854776806"));
	printf("FT atoi with long max + 1000: %i\n\n", ft_atoi("9223372036854776806"));
	printf("Regular atoi with long min - 1000: %i\n", atoi("-9223372036854776808"));
	printf("FT atoi with long min - 1000: %i\n\n", ft_atoi("-9223372036854776808"));
	printf("Regular atoi with '188888888888888488888888888888888': %i\n", atoi("188888888888888488888888888888888"));
	printf("FT atoi with '188888888888888488888888888888888': %i\n\n", ft_atoi("188888888888888488888888888888888"));
	printf("Regular atoi with '-188888888888888888888888888888888': %i\n", atoi("-188888888888888888888888888888888"));
	printf("FT atoi with '-188888888888888888888888888888888': %i\n\n", ft_atoi("-188888888888888888888888888888888"));

	printf("---------------------------\n\n");

}
