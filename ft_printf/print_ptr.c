/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:24:51 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/07 20:43:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


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
		count += print_char(n + '0');
	else
		count += print_char((n - 10) + 'a');
	return (count);
}

int	print_ptr(unsigned long int n)
{
	int	count;

	count = 0;
	count += print_str("0x");
	count += print_adr(n);
	return (count);
}
