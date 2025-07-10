/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:12:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/11 16:25:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Count the digits, check for minus.
// Append to string array one at a time with nbr % 10 + '0',
// after which nbr / 10. After done, reverse the string.

#include "ft_printf.h"

static int	count_len(long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	reverse_digit(char *itoa)
{
	char	temp;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(itoa) - 1;
	if (itoa[i] == '-')
		i++;
	while (itoa[i] && j > i)
	{
		temp = itoa[i];
		itoa[i] = itoa[j];
		itoa[j] = temp;
		i++;
		j--;
	}
}

char	*ft_ltoa(long n)
{
	char	*itoa;
	size_t	i;

	if (n == 0)
		return (ft_strdup("0"));
	itoa = (char *)malloc((count_len(n) + 1));
	if (!itoa)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		itoa[i++] = '-';
		n = -n;
	}
	while (n)
	{
		itoa[i++] = (n % 10) + '0';
		n /= 10;
	}
	itoa[i] = '\0';
	reverse_digit(itoa);
	return (itoa);
}
