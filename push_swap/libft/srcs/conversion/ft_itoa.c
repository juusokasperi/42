/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:12:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/30 16:43:32 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_reverse_digit(char *itoa)
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
	itoa = (char *)malloc((ft_count_digits(n, 10) + 1));
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
	ft_reverse_digit(itoa);
	return (itoa);
}
