/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 11:15:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	res = print_str(nbr_itoa);
	free(nbr_itoa);
	return (res);
}
