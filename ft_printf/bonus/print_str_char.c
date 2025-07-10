/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 11:18:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	print_str_handler(const char *str, t_flags flags)
{
	size_t	len;
	char	*str_width;
	char	*pad;
	int		res;

	if (!str)
		return (ft_putstr_fd("(null)", 1));
	if (flags.prec == 0)
		return (0);
	len = ft_strlen(str);
	if (flags.prec >= 0 && flags.prec < (int)len)
		len = flags.prec;
	if (flags.width < (int)len && flags.prec == -1)
		return (ft_putstr_fd((char *)str, 1));
	pad = pad_width(flags.width, len, 0);
	if (!pad)
		return (-1);
	str_width = format_string(str, pad, flags.left, flags.prec);
	if (!str_width)
		return (-1);
	res = ft_putstr_fd(str_width, 1);
	free(str_width);
	return (res);
}

static char	*append_padding(char const c, t_flags flags)
{
	char	*result;
	char	*pad;
	int		i;
	int		j;

	pad = pad_width(flags.width, 1, flags.zero);
	if (!pad)
		return (NULL);
	i = 0;
	j = 0;
	if (c == 0)
		result = (char *)malloc((ft_strlen(pad) + 1) * sizeof(char));
	else
		result = (char *)malloc((ft_strlen(pad) + 2) * sizeof(char));
	if (!result)
		return (ft_free((void **)&pad));
	if (flags.left == 1 && c)
		result[j++] = c;
	while (pad[i])
		result[j++] = pad[i++];
	if (flags.left == 0 && c)
		result[j++] = c;
	result[j] = '\0';
	ft_free((void **)&pad);
	return (result);
}

int	print_char(int c, t_flags flags)
{
	char	*new_str;
	int		res;

	if (flags.width < 2)
		return (ft_putchar_fd(c, 1));
	new_str = append_padding(c, flags);
	if (!new_str)
		return (-1);
	res = ft_putstr_fd(new_str, 1);
	if (c == 0 && res != -1)
		res += 1;
	ft_free((void **)&new_str);
	return (res);
}
