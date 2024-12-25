/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:24:51 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/06 23:14:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static char	*ft_xtoa(uintptr_t n, char *digits, int is_ptr)
{
	char	*xtoa;
	int		i;

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
	{
		xtoa[i++] = 'x';
		xtoa[i++] = '0';
	}
	xtoa[i] = '\0';
	ft_reverse_digit(xtoa);
	return (xtoa);
}

int	print_hexptr_handler(uintptr_t nbr, bool capital, bool is_ptr)
{
	int		res;
	char	*xtoa;
	char	*digits;

	if (capital)
		digits = "0123456789abcdef";
	else
		digits = "0123456789abcdef";
	res = 0;
	if (!nbr && is_ptr)
		return (ft_putstr_fd("(nil)", 1));
	xtoa = ft_xtoa(nbr, digits, is_ptr);
	if (!xtoa)
		return (-1);
	res = ft_putstr_fd(xtoa, 1);
	free(xtoa);
	return (res);
}

int	print_nbr_handler(int nbr)
{
	int		res;
	char	*nbr_itoa;
	long	long_nbr;

	long_nbr = (long)nbr;
	res = 0;
	nbr_itoa = ft_ltoa(long_nbr);
	if (!nbr_itoa)
		return (-1);
	res = ft_putstr_fd(nbr_itoa, 1);
	free(nbr_itoa);
	return (res);
}

int	print_unsigned_handler(unsigned int nbr)
{
	int		res;
	char	*nbr_itoa;

	res = 0;
	nbr_itoa = ft_ltoa(nbr);
	if (!nbr_itoa)
		return (-1);
	res = ft_putstr_fd(nbr_itoa, 1);
	free(nbr_itoa);
	return (res);
}
