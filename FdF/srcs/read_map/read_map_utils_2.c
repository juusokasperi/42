/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:09:36 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/11 21:20:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_is_valid(const char *hex)
{
	int			i;

	if (ft_strlen(hex) != 8)
		if (hex[8] != '\n')
			return (0);
	if (hex[0] != '0' && (hex[1] != 'x' && hex[1] != 'X'))
		return (0);
	i = 2;
	while (i < 8)
	{
		if (!ft_strrchr("0123456789ABCDEFabcdef", hex[i]))
			return (0);
		i++;
	}
	return (1);
}

uint32_t	hex_to_rgba(const char *hex)
{
	uint32_t	rgb;

	rgb = (uint32_t)ft_strtol(hex, NULL, 16);
	return (rgb << 8 | 0xFF);
}
