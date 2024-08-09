/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:25:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/08 23:02:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_un_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	print_unsigned_recursion(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr >= 10)
	{
		count += print_unsigned_recursion(nbr / 10);
		nbr = nbr % 10;
	}
	count += print_c(nbr + '0');
	return (count);
}

int	print_unsigned(unsigned int nbr, t_flags flags)
{
	int	count;
	int	len;

	count = 0;
	len = ft_un_len(nbr);
	if (flags.left_align == 0)
		count += pad_width(flags.width, len, flags.zero_pad);
	count += print_unsigned_recursion(nbr);
	if (flags.left_align == 1)
		count += pad_width(flags.width, len, flags.zero_pad);
	return (count);
}
