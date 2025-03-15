/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:24 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/15 09:59:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*append_positive(char *nbr_itoa, char positive)
{
	char	*res;
	int		i;

	res = malloc(ft_strlen(nbr_itoa) + 2);
	if (!res)
		return (ft_free((void **)&nbr_itoa));
	res[0] = positive;
	i = 0;
	while (nbr_itoa[i])
	{
		res[i + 1] = nbr_itoa[i];
		i++;
	}
	res[i + 1] = 0;
	ft_free((void **)&nbr_itoa);
	return (res);
}

static char	*build_nbr(int positive, char *nbr_itoa, int prec, int len)
{
	char		*res;
	const int	is_negative = (nbr_itoa[0] == '-');
	int			i;
	int			j;

	res = malloc(prec + 1 + is_negative + positive);
	if (!res)
		return (ft_free((void **)&nbr_itoa));
	i = 0;
	j = 0;
	if (positive)
		res[i++] = positive;
	else if (is_negative)
		res[i++] = nbr_itoa[j++];
	while ((prec-- + is_negative) > len)
		res[i++] = '0';
	while (nbr_itoa[j])
		res[i++] = nbr_itoa[j++];
	res[i] = 0;
	ft_free((void **)&nbr_itoa);
	return (res);
}

static char	*handle_prec_positive(char *nbr_itoa, int prec, char positive)
{
	char		*res;
	const int	len = ft_strlen(nbr_itoa);
	const int	is_negative = (nbr_itoa[0] == '-');

	if (positive && prec <= len)
		return (append_positive(nbr_itoa, positive));
	if ((prec + is_negative) <= len)
		return (nbr_itoa);
	res = build_nbr(positive, nbr_itoa, prec, len);
	return (res);
}

int	print_nbr_handler(int nbr, t_flags flags)
{
	char	*nbr_itoa;

	if (flags.prec == 0 && nbr == 0 && flags.positive)
		return (ft_putchar_fd(flags.positive, 1));
	else if (flags.prec == 0 && nbr == 0)
		return (0);
	if (nbr < 0)
		flags.positive = 0;
	nbr_itoa = ft_ltoa((long)nbr);
	if (!nbr_itoa)
		return (-1);
	nbr_itoa = handle_prec_positive(nbr_itoa, flags.prec, flags.positive);
	if (!nbr_itoa)
		return (-1);
	if (flags.width < (int)ft_strlen(nbr_itoa))
		return (print_and_free(nbr_itoa));
	nbr_itoa = append_padding_nbr(nbr_itoa, flags);
	if (!nbr_itoa)
		return (-1);
	return (print_and_free(nbr_itoa));
}
