/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:24 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 00:34:30 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_sign(t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->negative && flags->prec == -1)
	{
		count += print_c('-');
		flags->width--;
	}
	else if (flags->positive && flags->prec == -1)
		count += print_c(flags->positive);
	return (count);
}

static int	print_i(char *nbr_itoa, int nbr_len, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.negative)
	{
		if (flags.zero == 0 || flags.prec >= 0)
			count += print_c('-');
	}
	else if (flags.positive && !flags.zero)
		count += print_c(flags.positive);
	if (flags.prec >= 0)
		count += pad_width(flags.prec - 1, nbr_len - 1, 1);
	count += print_s(nbr_itoa);
	return (count);
}

static int	print_int(char *nbr_itoa, t_flags flags)
{
	int	count;
	int	nbr_len;

	count = 0;
	nbr_len = ft_strlen(nbr_itoa);
	if (flags.zero == 1)
		count += print_sign(&flags);
	if (flags.left == 1)
		count += print_i(nbr_itoa, nbr_len, flags);
	if (flags.prec >= 0 && flags.prec < nbr_len)
		flags.prec = nbr_len;
	if (flags.prec >= 0)
	{
		flags.width -= flags.prec;
		if (!flags.negative && flags.positive)
			flags.width--;
		count += pad_width(flags.width, 0, 0);
	}
	else
		count += pad_width(flags.width - (flags.positive > 0),
				nbr_len, flags.zero);
	if (flags.left == 0)
		count += print_i(nbr_itoa, nbr_len, flags);
	return (count);
}

static int	handle_zero(t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->positive)
		flags->width -= 1;
	if (flags->left == 1 && flags->positive)
		count += print_c(flags->positive);
	count += pad_width(flags->width, 0, 0);
	if (flags->left == 0 && flags->positive)
		count += print_c(flags->positive);
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
		flags->positive = 0;
		long_nbr = -long_nbr;
		if (flags->zero == 0)
			flags->width--;
	}
	if (flags->prec == 0 && long_nbr == 0)
		return (count += handle_zero(flags));
	nbr_itoa = ft_ltoa(long_nbr);
	if (!nbr_itoa)
		return (0);
	count += print_int(nbr_itoa, *flags);
	free(nbr_itoa);
	return (count);
}
