/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strchar_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/09 12:20:17 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_char(char c, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.left_align == 0)
		count += pad_width(flags.width, 1, 0);
	count += print_c(c);
	if (flags.left_align == 1)
		count += pad_width(flags.width, 1, 0);
	return (count);
}

int	print_c(char c)
{
	write (1, &c, 1);
	return (1);
}

int	print_s(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i += print_c(str[i]);
	return (i);
}

int	print_str_handler(const char *str, t_flags flags)
{
	int	i;
	int	len;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		str = "(null)";
	len = str_len(str);
	if (flags.precision >= 0 && flags.precision < len)
		len = flags.precision;
	if (flags.left_align == 0)
		count += pad_width(flags.width, len, 0);
	while (i < len)
		count += print_c(str[i++]);
	if (flags.left_align == 1)
		count += pad_width(flags.width, len, 0);
	return (count);
}
