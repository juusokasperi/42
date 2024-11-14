/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:25:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 11:15:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_handler(unsigned int nbr)
{
	int		res;
	char	*nbr_itoa;

	res = 0;
	nbr_itoa = ft_ltoa(nbr);
	if (!nbr_itoa)
		return (-1);
	res = print_str(nbr_itoa);
	free(nbr_itoa);
	return (res);
}
