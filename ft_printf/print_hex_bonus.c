/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:23:34 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 20:25:43 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hash(int capital)
{
	if (capital)
		return (print_s("0X"));
	return (print_s("0x"));
}

static int	print_x(char *hex_xtoa, int hex_len, t_flags flags, int capital)
{
	int	count;

	count = 0;
	if (flags.hash && capital && !flags.zero_pad)
		count += print_hash(1);
	else if (flags.hash && !flags.zero_pad)
		count += print_hash(0);
	if (flags.precision >= 0)
		count += pad_width(flags.precision - 1, hex_len - 1, 1);
	count += print_s(hex_xtoa);
	return (count);
}

static int	print_hex(char *hex_xtoa, t_flags flags, int capital)
{
	int	count;
	int	hex_len;

	count = 0;
	hex_len = str_len(hex_xtoa);
	if (flags.left_align == 1)
		count += print_x(hex_xtoa, hex_len, flags, capital);
	if (flags.precision >= 0 && flags.precision < hex_len)
		flags.precision = hex_len;
	if (flags.precision >= 0)
	{
		if (flags.hash)
			flags.width -= 2;
		flags.width -= flags.precision;
		count += pad_width(flags.width, 0, 0);
	}
	else
	{
		if (flags.zero_pad && flags.hash)
			count += print_hash(capital);
		count += pad_width(flags.width - (flags.hash), hex_len, flags.zero_pad);
	}
	if (flags.left_align == 0)
		count += print_x(hex_xtoa, hex_len, flags, capital);
	return (count);
}

int	print_hex_handler(unsigned int nbr, int capital, t_flags *flags)
{
	int		count;
	char	*hex_xtoa;

	count = 0;
	if (flags->precision == 0 && nbr == 0)
		return (pad_width(flags->width, 0, 0));
	if (nbr == 0 && flags->hash)
		flags->hash = 0;
	hex_xtoa = ft_xtoa(nbr, capital);
	if (!hex_xtoa)
		return (0);
	count += print_hex(hex_xtoa, *flags, capital);
	free(hex_xtoa);
	return (count);
}
