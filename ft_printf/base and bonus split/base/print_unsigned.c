/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:25:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 19:46:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_handler(unsigned int nbr)
{
	int		count;
	char	*nbr_itoa;

	count = 0;
	nbr_itoa = ft_ltoa(nbr);
	if (!nbr_itoa)
		return (0);
	count += print_s(nbr_itoa);
	free(nbr_itoa);
	return (count);
}
