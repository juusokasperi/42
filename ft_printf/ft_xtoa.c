/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:12:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/13 14:47:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Count the digits, check for minus.
// Append to string array one at a time with nbr % 10 + '0',
// after which nbr / 10. After done, reverse the string.

#include "ft_printf.h"

static int	count_len(uintptr_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	reverse_digit(char *xtoa)
{
	char	temp;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(xtoa) - 1;
	while (i < j)
	{
		temp = xtoa[i];
		xtoa[i] = xtoa[j];
		xtoa[j] = temp;
		i++;
		j--;
	}
}

char	*ft_xtoa(uintptr_t n, int capital)
{
	char	*xtoa;
	int		i;
	char	*digits;

	if (capital)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	if (n == 0)
		return (ft_strdup("0"));
	xtoa = (char *)malloc(count_len(n) + 1);
	if (!xtoa)
		return (NULL);
	i = 0;
	while (n)
	{
		xtoa[i++] = digits[n % 16];
		n /= 16;
	}
	xtoa[i] = '\0';
	reverse_digit(xtoa);
	return (xtoa);
}
