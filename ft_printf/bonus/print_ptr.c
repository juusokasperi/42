/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:24:51 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 17:32:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_x(char *ptr_xtoa, int ptr_len, t_flags flags)
{
	int	count;

	count = 0;
	if (!flags.zero)
		count += print_s("0x");
	if (flags.prec >= 0)
		count += pad_width(flags.prec - 1, ptr_len - 1, 1);
	count += print_s(ptr_xtoa);
	return (count);
}

static int	print_ptr(char *ptr_xtoa, t_flags flags)
{
	int	count;
	int	ptr_len;

	count = 0;
	ptr_len = ft_strlen(ptr_xtoa);
	if (flags.left == 1)
		count += print_x(ptr_xtoa, ptr_len, flags);
	if (flags.prec >= 0 && flags.prec < ptr_len)
		flags.prec = ptr_len;
	if (flags.prec >= 0)
	{
		flags.width -= flags.prec;
		count += pad_width(flags.width, 0, 0);
	}
	else
	{
		if (flags.zero)
			count += (print_s("0x"));
		count += pad_width(flags.width, ptr_len, flags.zero);
	}
	if (flags.left == 0)
		count += print_x(ptr_xtoa, ptr_len, flags);
	return (count);
}

static int	format_ptr(char *ptr_xtoa, t_flags flags)
{
	int		ptr_len;
	char	*pad;
	char	*str;
	char	*new_str;

	ptr_len = ft_strlen(ptr_xtoa);
	if (flags.left == 1)
		str = ft_strdup("0x");
	if (flags.prec >= 0)
	{
		pad = pad_width(flags.prec - 1, ptr_len - 1, 1);
		new_str = ft_strjoin(str, pad);
		new_str = ft_strjoin(new_str, ptr_xtoa);
	}
	else if (flags.prec < 0)
	{
		pad = pad_width(flags.width, ptr_len, 0);
		new_str = ft_strjoin(str, ptr_xtoa);
		new_str = ft_strjoin(new_str, pad);
	}
	free(pad);
	free(str);
	return (new_str);
}

int	print_ptr_handler(uintptr_t nbr, t_flags flags)
{
	int		res;
	char	*ptr_xtoa;
	int		len;
	char	*pad;
	char	*new_str;

	if (!nbr)
		return (print_s("(nil)", ft_strlen("(nil)")));
	flags.width -= 2;
	ptr_xtoa = ft_xtoa(nbr, 0);
	if (!ptr_xtoa)
		return (-1);
	new_str = format(ptr_xtoa, flags);
	if (!new_str)
		return (-1);
	res = print_s(new_str, ft_strlen(new_str));
	free(ptr_xtoa);
	free(new_str);
	return (res);
}
