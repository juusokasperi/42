/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:24:51 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 00:34:39 by jrinta-          ###   ########.fr       */
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

int	print_ptr_handler(uintptr_t nbr, t_flags flags)
{
	int		count;
	char	*ptr_xtoa;

	count = 0;
	if (!nbr)
		return count += print_s("(nil)");
	flags.width -= 2;
	if (flags.prec == 0 && nbr == 0)
	{
		count += print_s("0x");
		return (count += pad_width(flags.width, 0, 0));
	}
	ptr_xtoa = ft_xtoa(nbr, 0);
	if (!ptr_xtoa)
		return (0);
	count += print_ptr(ptr_xtoa, flags);
	free(ptr_xtoa);
	return (count);
}
