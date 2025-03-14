/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:12:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 17:37:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int	i;

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

char	*ft_itoa(int n)
{
	char	*itoa;
	size_t	i;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
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
