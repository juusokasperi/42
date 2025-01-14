/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:58:23 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/13 17:24:47 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	hex_to_rgba(const char *hex)
{
	uint32_t	rgb;

	rgb = (uint32_t)ft_strtol(hex, NULL, 16);
	return (rgb << 8 | 0xFF);
}

int	color_is_valid(const char *hex)
{
	int	i;
	int	len;

	len = ft_strlen(hex);
	if (hex[len - 1] == '\n')
		len--;
	if (len > 8 || (hex[0] != '0' && (hex[1] != 'x' && hex[1] != 'X')))
		return (0);
	i = 2;
	while (i < len)
	{
		if (!ft_strrchr("0123456789ABCDEFabcdef", hex[i]))
			return (0);
		i++;
	}
	return (1);
}
