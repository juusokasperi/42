/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:12:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/21 09:54:30 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int	handle_ptr(char *xtoa, int i)
{
	xtoa[i++] = 'x';
	xtoa[i++] = '0';
	return (i);
}

char	*ft_xtoa(uintptr_t n, int capital, int is_ptr)
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
	xtoa = (char *)malloc(ft_count_digits(n, 16) + 1 + (is_ptr * 2));
	if (!xtoa)
		return (NULL);
	i = 0;
	while (n)
	{
		xtoa[i++] = digits[n % 16];
		n /= 16;
	}
	if (is_ptr)
		i = handle_ptr(xtoa, i);
	xtoa[i] = '\0';
	reverse_digit(xtoa);
	return (xtoa);
}
