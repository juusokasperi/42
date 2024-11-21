/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 16:27:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	print_s(const char *str, size_t len)
{
	return (write(1, str, len));
}

static char	*format_string(const char *str, char *pad, int left)
{
	char *str_width;

	if (left == 0)
		str_width = ft_strjoin(pad, str);
	else
		str_width = ft_strjoin(str, pad);
	free(pad);
	return (str_width);
}

int	print_str_handler(const char *str, t_flags flags)
{
	size_t	len;
	char	*str_width;
	char	*pad;
	int		res;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.prec >= 0 && flags.prec < (int) len)
		len = flags.prec;
	pad = pad_width(flags.width, len, 0);
	if (pad)
	{
		len += ft_strlen(pad);
		str_width = format_string(str, pad, flags.left);
	}
	else
		str_width = ft_strdup(str);
	if (!str_width)
		return (-1);
	res = print_s(str_width, len);
	free(str_width);
	return (res);
}
