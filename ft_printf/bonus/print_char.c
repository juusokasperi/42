/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/14 14:22:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		return (print_c(c));
	new_str = append_padding(c, flags);
	if (!new_str)
		return (-1);
	res = print_s(new_str);
	if (c == 0)
		res += 1;
	ft_free((void **)&new_str);
	return (res);
}

int	print_c(char c)
{
	return (write (1, &c, 1));
}
