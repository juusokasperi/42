/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:25:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/07 20:40:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_recursion(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr >= 10)
	{
		count += print_unsigned_recursion(nbr / 10);
		nbr = nbr % 10;
	}
	count += print_char(nbr + '0');
	return (count);
}

int	print_unsigned(unsigned int nbr)
{
	int	count;

	count = 0;
	count += print_unsigned_recursion(nbr);
	return (count);
}
