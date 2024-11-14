/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:45:13 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 16:19:17 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
char	*pad_width(int width, int size, int zero_pad)
{
	int		i;
	char	*pad;

	i = 0;
	if (width - size + 1 < 0)
		return (NULL);
	pad = (char *)malloc((width - size + 1) * sizeof(char));
	if (!pad)
		return (NULL);
	while (width - size > 0)
	{
		if (zero_pad)
			pad[i] = '0';
		else
			pad[i] = ' ';
		width--;
		i++;
	}
	pad[i] = '\0';
	return (pad);
}

int	is_flag(char c)
{
	return (ft_strchr("cspdiuxX%-0.# +*", c) || ft_isdigit(c));
}
