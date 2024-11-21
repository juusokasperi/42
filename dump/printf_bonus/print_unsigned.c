/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:25:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 00:33:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_i(char *nbr_itoa, int nbr_len, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.prec >= 0)
		count += pad_width(flags.prec - 1, nbr_len - 1, 1);
	count += print_s(nbr_itoa);
	return (count);
}

static int	print_unsigned_int(char *nbr_itoa, t_flags flags)
{
	int	count;
	int	nbr_len;

	count = 0;
	nbr_len = ft_strlen(nbr_itoa);
	if (flags.left == 1)
		count += print_i(nbr_itoa, nbr_len, flags);
	if (flags.prec >= 0 && flags.prec < nbr_len)
		flags.prec = nbr_len;
	if (flags.prec >= 0)
	{
		flags.width -= flags.prec;
		count += pad_width(flags.width, 0, 0);
	}
	else
		count += pad_width(flags.width, nbr_len, flags.zero);
	if (flags.left == 0)
		count += print_i(nbr_itoa, nbr_len, flags);
	return (count);
}

int	print_unsigned_handler(unsigned int nbr, t_flags flags)
{
	int		count;
	char	*nbr_itoa;

	count = 0;
	if (flags.prec == 0 && nbr == 0)
		return (pad_width(flags.width, 0, 0));
	nbr_itoa = ft_ltoa(nbr);
	if (!nbr_itoa)
		return (0);
	count += print_unsigned_int(nbr_itoa, flags);
	free(nbr_itoa);
	return (count);
}
