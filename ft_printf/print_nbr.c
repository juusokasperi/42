/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/10 15:42:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_sign(t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->negative && flags->precision == -1)
	{
		count += print_c('-');
		flags->width--;
	}
	else if (flags->positive_sign && flags->precision == -1)
		count += print_c(flags->positive_sign);
	return (count);
}

static int	print_i(char *nbr_itoa, int nbr_len, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.negative)
	{
		if (flags.zero_pad == 0 || flags.precision >= 0)
			count += print_c('-');
	}
	else if (flags.positive_sign && !flags.zero_pad)
		count += print_c(flags.positive_sign);
	if (flags.precision >= 0)
		count += pad_width(flags.precision - 1, nbr_len - 1, 1);
	count += print_s(nbr_itoa);
	return (count);
}

static int	print_int(char *nbr_itoa, t_flags flags)
{
	int	count;
	int	nbr_len;

	count = 0;
	nbr_len = ft_strlen(nbr_itoa);
	if (flags.zero_pad == 1)
		count += print_sign(&flags);
	if (flags.left_align == 1)
		count += print_i(nbr_itoa, nbr_len, flags);
	if (flags.precision >= 0 && flags.precision < nbr_len)
		flags.precision = nbr_len;
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		if (!flags.negative && flags.positive_sign)
			flags.width--;
		count += pad_width(flags.width, 0, 0);
	}
	else
		count += pad_width(flags.width - (flags.positive_sign > 0),
			nbr_len, flags.zero_pad);
	if (flags.left_align == 0)
		count += print_i(nbr_itoa, nbr_len, flags);
	return (count);
}

int	print_nbr_handler(int nbr, t_flags *flags)
{
	int		count;
	char	*nbr_itoa;
	long	long_nbr;

	long_nbr = (long)nbr;
	count = 0;
	if (long_nbr < 0)
	{
		flags->negative = 1;
		long_nbr = -long_nbr;
		if (flags->zero_pad == 0)
			flags->width--;
	}
	if (flags->precision == 0 && long_nbr == 0)
		return (pad_width(flags->width, 0, 0));
	nbr_itoa = ft_itoa(long_nbr);
	if (!nbr_itoa)
		return (0);
	count += print_int(nbr_itoa, *flags);
	free(nbr_itoa);
	return (count);
}
