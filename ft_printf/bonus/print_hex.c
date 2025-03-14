/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:23:34 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/14 14:30:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*append_precision(char *hex_xtoa, int prec)
{
	char	*res;
	int		hex_len;
	int		i;
	int		j;

	hex_len = ft_strlen(hex_xtoa);
	res = malloc(prec + 1);
	if (!res)
		return (ft_free((void **)&hex_xtoa));
	i = -1;
	while (++i < prec - hex_len)
		res[i] = '0';
	j = 0;
	while (i < prec && hex_xtoa[j])
		res[i++] = hex_xtoa[j++];
	res[i] = 0;
	ft_free((void **)&hex_xtoa);
	return (res);
}

static char	*append_hash(char *hex_xtoa, int capital)
{
	char	*res;
	char	hash;
	int		i;

	if (has_only_zeros(hex_xtoa))
		return (hex_xtoa);
	if (capital)
		hash = 'X';
	else
		hash = 'x';
	res = malloc(ft_strlen(hex_xtoa) + 3);
	if (!res)
		return (ft_free((void **)&hex_xtoa));
	res[0] = '0';
	res[1] = hash;
	i = -1;
	while (hex_xtoa[++i])
		res[i + 2] = hex_xtoa[i];
	hex_xtoa[i] = 0;
	ft_free((void **)&hex_xtoa);
	return (res);
}

static char	*handle_zero_flag(char *hex_xtoa, char *pad, int hash)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(hex_xtoa) + ft_strlen(pad) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (hash && i < 2)
	{
		res[i] = hex_xtoa[i];
		i++;
	}
	j = 0;
	while (pad[j])
		res[i++] = pad[j++];
	if (hash)
		j = 2;
	else
		j = 0;
	while (hex_xtoa[j])
		res[i++] = hex_xtoa[j++];
	res[i] = 0;
	return (res);
}

static char	*append_padding(char *hex_xtoa, t_flags flags)
{
	char	*res;
	char	*pad;

	pad = pad_width(flags.width, ft_strlen(hex_xtoa), flags.zero);
	if (!pad)
		return (ft_free((void **)&hex_xtoa));
	if (flags.zero)
		res = handle_zero_flag(hex_xtoa, pad, flags.hash);
	else
	{
		if (flags.left == 0)
			res = ft_strjoin(pad, hex_xtoa);
		else
			res = ft_strjoin(hex_xtoa, pad);
	}
	ft_free((void **)&hex_xtoa);
	ft_free((void **)&pad);
	if (!res)
		return (NULL);
	return (res);
}

int	print_hex_handler(unsigned int nbr, int capital, t_flags flags)
{
	char	*hex_xtoa;

	if (nbr == 0 && flags.prec == 0)
		return (0);
	hex_xtoa = ft_xtoa(nbr, capital);
	if (!hex_xtoa)
		return (-1);
	if ((int)ft_strlen(hex_xtoa) < flags.prec)
		hex_xtoa = append_precision(hex_xtoa, flags.prec);
	if (!hex_xtoa)
		return (-1);
	if (flags.hash)
		hex_xtoa = append_hash(hex_xtoa, capital);
	if (!hex_xtoa)
		return (-1);
	if (flags.width < (int)ft_strlen(hex_xtoa))
		return (print_and_free(hex_xtoa));
	hex_xtoa = append_padding(hex_xtoa, flags);
	if (!hex_xtoa)
		return (-1);
	return (print_and_free(hex_xtoa));
}
