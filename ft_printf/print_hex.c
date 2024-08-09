/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:23:34 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/09 12:06:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		len++;
		n /= 16;
	}
	return (len);
}

int	print_hex_recursion(unsigned long int n, char c)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += print_hex_recursion(n / 16, c);
		n = n % 16;
	}
	if (n < 10)
		count += print_c(n + '0');
	else
		count += print_c((n - 10) + c);
	return (count);
}

int	print_hex(unsigned int nbr, int capital, t_flags flags)
{
	char	c;
	int		len;
	int		count;

	c = 'a';
	len = ft_hexlen(nbr);
	if (flags.hash)
		len += 2;
	count = 0;
	if (capital)
		c = 'A';
	if (flags.left_align == 0)
		count += pad_width(flags.width, len, flags.zero_pad);
	if (flags.hash)
	{
		if (capital)
			count += print_s("0X");
		else
			count += print_s("0x");
	}
	count += print_hex_recursion(nbr, c);
	if (flags.left_align == 1)
		count += pad_width(flags.width, len, flags.zero_pad);
	return (count);
}
