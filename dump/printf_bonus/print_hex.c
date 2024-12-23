/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:23:34 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 00:34:12 by jrinta-          ###   ########.fr       */
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
	if (flags.hash && capital && !flags.zero)
		count += print_hash(1);
	else if (flags.hash && !flags.zero)
		count += print_hash(0);
	if (flags.prec >= 0)
		count += pad_width(flags.prec - 1, hex_len - 1, 1);
	count += print_s(hex_xtoa);
	return (count);
}

static int	print_hex(char *hex_xtoa, t_flags flags, int capital)
{
	int	count;
	int	hex_len;

	count = 0;
	hex_len = ft_strlen(hex_xtoa);
	if (flags.left == 1)
		count += print_x(hex_xtoa, hex_len, flags, capital);
	if (flags.prec >= 0 && flags.prec < hex_len)
		flags.prec = hex_len;
	if (flags.prec >= 0)
	{
		if (flags.hash)
			flags.width -= 2;
		flags.width -= flags.prec;
		count += pad_width(flags.width, 0, 0);
	}
	else
	{
		if (flags.zero && flags.hash)
			count += print_hash(capital);
		count += pad_width(flags.width - (flags.hash), hex_len, flags.zero);
	}
	if (flags.left == 0)
		count += print_x(hex_xtoa, hex_len, flags, capital);
	return (count);
}

int	print_hex_handler(unsigned int nbr, int capital, t_flags *flags)
{
	int		count;
	char	*hex_xtoa;

	count = 0;
	if (flags->prec == 0 && nbr == 0)
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
