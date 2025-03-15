/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:24:51 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/15 09:59:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*append_hash(char *ptr_xtoa)
{
	char	*res;
	int		i;

	res = malloc(ft_strlen(ptr_xtoa) + 3);
	if (!res)
		return (ft_free((void **)&ptr_xtoa));
	res[0] = '0';
	res[1] = 'x';
	i = 0;
	while (ptr_xtoa[i])
	{
		res[i + 2] = ptr_xtoa[i];
		i++;
	}
	res[i + 2] = 0;
	ft_free((void **)&ptr_xtoa);
	return (res);
}

static char	*append_prec(char *ptr_xtoa, int prec)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	if (prec == -1)
		return (ptr_xtoa);
	len = ft_strlen(ptr_xtoa);
	if (len < prec)
		res = malloc(prec + 1);
	else
		res = malloc(len + 1);
	if (!res)
		return (ft_free((void **)&ptr_xtoa));
	res[0] = ptr_xtoa[0];
	res[1] = ptr_xtoa[1];
	i = 2;
	while (i - 2 < prec - (len - 2))
		res[i++] = '0';
	j = 2;
	while (ptr_xtoa[j])
		res[i++] = ptr_xtoa[j++];
	ft_free((void **)&ptr_xtoa);
	return (res);
}

static char	*handle_zero_flag(char *hex_xtoa, char *pad)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(hex_xtoa) + ft_strlen(pad) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < 2)
		res[i] = hex_xtoa[i];
	j = 0;
	while (pad[j])
		res[i++] = pad[j++];
	j = 2;
	while (hex_xtoa[j])
		res[i++] = hex_xtoa[j++];
	res[i] = 0;
	return (res);
}

static char	*append_padding(char *ptr_xtoa, t_flags flags)
{
	char	*res;
	char	*pad;

	pad = pad_width(flags.width, ft_strlen(ptr_xtoa), flags.zero);
	if (!pad)
		return (ft_free((void **)&ptr_xtoa));
	if (flags.zero)
		res = handle_zero_flag(ptr_xtoa, pad);
	else
	{
		if (flags.left == 0)
			res = ft_strjoin(pad, ptr_xtoa);
		else
			res = ft_strjoin(ptr_xtoa, pad);
	}
	ft_free((void **)&ptr_xtoa);
	ft_free((void **)&pad);
	if (!res)
		return (NULL);
	return (res);
}

int	print_ptr_handler(uintptr_t nbr, t_flags flags)
{
	char	*ptr_xtoa;

	if (!nbr)
		return (ft_putstr_fd("(nil)", 1));
	if (nbr != 0 && flags.prec == 0)
		flags.prec = -1;
	ptr_xtoa = ft_xtoa(nbr, 0);
	if (!ptr_xtoa)
		return (-1);
	ptr_xtoa = append_hash(ptr_xtoa);
	if (!ptr_xtoa)
		return (-1);
	ptr_xtoa = append_prec(ptr_xtoa, flags.prec);
	if (!ptr_xtoa)
		return (-1);
	if (flags.width < (int)ft_strlen(ptr_xtoa))
		return (print_and_free(ptr_xtoa));
	ptr_xtoa = append_padding(ptr_xtoa, flags);
	if (!ptr_xtoa)
		return (-1);
	return (print_and_free(ptr_xtoa));
}
