/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 16:35:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*width_char(char const *s, char const c, int left)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc((ft_strlen(s) + 2) * sizeof(char));
	if (!result)
		return (NULL);
	if (left == 0)
		result[j++] = c;
	while (s[i])
		result[j++] = s[i++];
	if (left == 1)
		result[j++] = c;
	result[j] = '\0';
	return (result);
}

int	print_char(char c, t_flags flags)
{
	char	*pad;
	char	*new_str;
	int		res;

	pad = pad_width(flags.width, 1, 0);
	if (pad)
		new_str = width_char(pad, c, flags.left);
	else
		return (print_c(c));
	free(pad);
	if (!new_str)
		return (-1);
	res = print_s(new_str, ft_strlen(new_str));
	free(new_str);
	return (res);
}

int	print_c(char c)
{
	return (write (1, &c, 1));
}
