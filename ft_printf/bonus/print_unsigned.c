/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:25:54 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 12:13:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*handle_precision(char *nbr_itoa, int prec)
{
	char	*res;
	int		nbr_len;
	int		i;
	int		j;

	nbr_len = ft_strlen(nbr_itoa);
	if (nbr_len >= prec)
		return (nbr_itoa);
	res = malloc(prec + 1);
	if (!res)
		return (ft_free((void **)&nbr_itoa));
	i = 0;
	while (prec-- > nbr_len)
		res[i++] = '0';
	j = 0;
	while (nbr_itoa[j])
		res[i++] = nbr_itoa[j++];
	res[i] = 0;
	ft_free((void **)&nbr_itoa);
	return (res);
}

static char	*handle_zero_flag(char *nbr_itoa, char *pad)
{
	char	*res;
	int		i;
	int		j;
	int		y;

	res = malloc(ft_strlen(nbr_itoa) + ft_strlen(pad) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	y = 0;
	if (nbr_itoa[0] == ' ' || nbr_itoa[0] == '+' || nbr_itoa[0] == '-')
		res[i++] = nbr_itoa[j++];
	while (pad[y])
		res[i++] = pad[y++];
	while (nbr_itoa[j])
		res[i++] = nbr_itoa[j++];
	res[i] = 0;
	return (res);
}

char	*append_padding_nbr(char *nbr_itoa, t_flags flags)
{
	char	*res;
	char	*pad;

	pad = pad_width(flags.width, ft_strlen(nbr_itoa), flags.zero);
	if (!pad)
		return (ft_free((void **)&nbr_itoa));
	if (flags.zero)
		res = handle_zero_flag(nbr_itoa, pad);
	else
	{
		if (flags.left == 0)
			res = ft_strjoin(pad, nbr_itoa);
		else
			res = ft_strjoin(nbr_itoa, pad);
	}
	ft_free((void **)&nbr_itoa);
	ft_free((void **)&pad);
	if (!res)
		return (NULL);
	return (res);
}

int	print_unsigned_handler(unsigned int nbr, t_flags flags)
{
	char	*nbr_itoa;

	if (nbr == 0 && flags.prec == 0)
		return (0);
	nbr_itoa = ft_ltoa(nbr);
	if (!nbr_itoa)
		return (-1);
	nbr_itoa = handle_precision(nbr_itoa, flags.prec);
	if (!nbr_itoa)
		return (-1);
	if (flags.width < (int)ft_strlen(nbr_itoa))
		return (print_and_free(nbr_itoa));
	nbr_itoa = append_padding_nbr(nbr_itoa, flags);
	if (!nbr_itoa)
		return (-1);
	return (print_and_free(nbr_itoa));
}
