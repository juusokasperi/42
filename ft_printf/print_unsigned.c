/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:25:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/11 20:15:47 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_i(char *nbr_itoa, int nbr_len, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.precision >= 0)
		count += pad_width(flags.precision - 1, nbr_len - 1, 1);
	count += print_s(nbr_itoa);
	return (count);
}

static int	print_unsigned_int(char *nbr_itoa, t_flags flags)
{
	int	count;
	int	nbr_len;

	count = 0;
	nbr_len = ft_strlen(nbr_itoa);
	if (flags.left_align == 1)
		count += print_i(nbr_itoa, nbr_len, flags);
	if (flags.precision >= 0 && flags.precision < nbr_len)
		flags.precision = nbr_len;
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		count += pad_width(flags.width, 0, 0);
	}
	else
		count += pad_width(flags.width, nbr_len, flags.zero_pad);
	if (flags.left_align == 0)
		count += print_i(nbr_itoa, nbr_len, flags);
	return (count);
}

int	print_unsigned_handler(unsigned int nbr, t_flags flags)
{
	int		count;
	char	*nbr_itoa;

	count = 0;
	if (flags.precision == 0 && nbr == 0)
		return (pad_width(flags.width, 0, 0));
	nbr_itoa = ft_itoa(nbr);
	if (!nbr_itoa)
		return (0);
	count += print_unsigned_int(nbr_itoa, flags);
	free(nbr_itoa);
	return (count);
}
