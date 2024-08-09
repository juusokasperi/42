/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:24:51 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/08 22:48:27 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptrlen(unsigned long int n)
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

int	print_adr(unsigned long int n)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += print_adr(n / 16);
		n = n % 16;
	}
	if (n < 10)
		count += print_c(n + '0');
	else
		count += print_c((n - 10) + 'a');
	return (count);
}

int	print_ptr(unsigned long int n, t_flags flags)
{
	int	count;
	int	len;

	len = ft_ptrlen(n) + 2;
	count = 0;
	if (flags.left_align == 0)
		count += pad_width(flags.width, len, flags.zero_pad);
	count += print_s("0x");
	count += print_adr(n);
	if (flags.left_align == 1)
		count += pad_width(flags.width, len, flags.zero_pad);
	return (count);
}
