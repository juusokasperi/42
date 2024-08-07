/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:23:34 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/07 20:42:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		count += print_char(n + '0');
	else
		count += print_char((n - 10) + c);
	return (count);
}

int	print_hex(unsigned int nbr, int capital)
{
	char	c;
	int		count;

	count = 0;
	if (capital)
		c = 'A';
	else
		c = 'a';
	count += print_hex_recursion(nbr, c);
	return (count);
}
