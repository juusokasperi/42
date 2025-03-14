/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/14 14:29:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_s(const char *str)
{
	return (write(1, str, ft_strlen(str)));
}

static char	*truncate_str(const char *str, int prec)
{
	char	*res;
	int		i;

	if (prec == -1)
		return (ft_strdup(str));
	res = malloc(prec + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < prec)
		res[i] = str[i];
	return (res);
}

static char	*format_string(const char *str, char *pad, int left, int prec)
{
	char	*tmp;
	char	*res;

	if (prec >= (int)ft_strlen(str))
	{
		if (left == 0)
			res = ft_strjoin(pad, str);
		else
			res = ft_strjoin(str, pad);
	}
	else
	{
		tmp = truncate_str(str, prec);
		if (!tmp)
			return (ft_free((void **)&pad));
		if (left == 0)
			res = ft_strjoin(pad, tmp);
		else
			res = ft_strjoin(tmp, pad);
		ft_free((void **)&tmp);
	}
	ft_free((void **)&pad);
	return (res);
}

//	Tsekkaa koulun koneella toimiiko precision stringin kanssa,
//	macilla ei toimi.
//	Tsekkaa koulun koneella toimiiko zero pad stringin kanssa.
int	print_str_handler(const char *str, t_flags flags)
{
	size_t	len;
	char	*str_width;
	char	*pad;
	int		res;

	if (!str)
		return (print_s("(null)"));
	len = ft_strlen(str);
	if (flags.prec == 0)
		return (0);
	if (flags.prec >= 0 && flags.prec < (int)len)
		len = flags.prec;
	if (flags.width < (int)len && flags.prec == -1)
		return (print_s(str));
	pad = pad_width(flags.width, len, flags.zero);
	if (!pad)
		return (-1);
	str_width = format_string(str, pad, flags.left, flags.prec);
	if (!str_width)
		return (-1);
	res = print_s(str_width);
	free(str_width);
	return (res);
}
