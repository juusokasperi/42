/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/07 20:40:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int	print_nbr_recursion(int nbr)
{
	int	count;

	count = 0;
	if (nbr >= 10)
	{
		count += print_nbr_recursion(nbr / 10);
		nbr = nbr % 10;
	}
	count += print_char(nbr + '0');
	return (count);
}

int	print_nbr(int nbr)
{
	int	count;

	count = 0;
	if (nbr == -2147483648)
		return (print_str("-2147483648"));
	if (nbr < 0)
	{
		count += print_char('-');
		nbr = -nbr;
	}
	count += print_nbr_recursion(nbr);
	return (count);
}
