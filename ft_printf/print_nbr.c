/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/09 21:59:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_sign(int nbr, t_flags *flags)
{
	int	count;

	count = 0;
	if (nbr < 0 && flags->precision == -1)
	{
		count += print_c('-');
		flags->width--;
	}
	else if (flags->plus)
		count += print_c('+');
	else if (flags->space)
		count += print_c(' ');
	return (count);
}

int	print_i(char *nbr_itoa, int nbr, int nbr_len, t_flags flags)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		if (flags.zero_pad == 0 || flags.precision >= 0)
			count += print_c('-');
	}
	else if (flags.plus && !flags.zero_pad)
		count += print_c('+');
	else if (flags.space && !flags.zero_pad)
		count += print_c(' ');
	if (flags.precision >= 0)
		count += pad_width(flags.precision - 1, nbr_len - 1, 1);
	count += print_s(nbr_itoa);
	return (count);
}

int	print_int(char *nbr_itoa, int nbr, t_flags flags)
{
	int	count;
	int	nbr_len;

	count = 0;
	nbr_len = ft_strlen(nbr_itoa);
	if (flags.zero_pad == 1)
		count += print_sign(nbr, &flags);
	if (flags.left_align == 1)
		count += print_i(nbr_itoa, nbr, nbr_len, flags);
	if (flags.precision >= 0 && flags.precision < nbr_len)
		flags.precision = nbr_len;
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		count += pad_width(flags.width, 0, 0);
	}
	else
		count += pad_width(flags.width - flags.plus - flags.space,
			nbr_len, flags.zero_pad);
	if (flags.left_align == 0)
		count += print_i(nbr_itoa, nbr, nbr_len, flags);
	return (count);
}

int	print_nbr(int nbr, t_flags flags)
{
	int		count;
	int		nb;
	char	*nbr_itoa;

	nb = nbr;
	count = 0;
	if (nb < 0)
	{
		nb = -nb;
		if (flags.zero_pad == 0)
			flags.width--;
	}
	if (flags.precision == 0 && nbr == 0)
		return (pad_width(flags.width, 0, 0));
	nbr_itoa = ft_itoa(nb);
	if (!nbr_itoa)
		return (0);
	count += print_int(nbr_itoa, nbr, flags);
	free(nbr_itoa);
	return (count);
}
