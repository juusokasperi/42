/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dual_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:05:00 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/10 14:37:17 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	parse_first_color(char **colors, t_rgb *color_1)
{
	bool	result;

	result = parse_rgb(colors[0], color_1);
	if (!result)
	{
		free_split(colors);
		return (false);
	}
	return (true);
}

static bool	parse_second_color(char **colors, t_rgb *color_2)
{
	bool	result;

	if (colors[1])
	{
		result = parse_rgb(colors[1], color_2);
		if (!result)
		{
			free_split(colors);
			return (false);
		}
	}
	else
	{
		*color_2 = rgb(225, 225, 225);
	}
	return (true);
}

bool	parse_dual_rgb(char *str, t_rgb *color_1, t_rgb *color_2)
{
	char	**colors;

	if (!str || !color_1 || !color_2)
		return (false);
	colors = ft_split(str, '/');
	if (!colors || !colors[0])
	{
		if (colors)
			free_split(colors);
		printf("Error\nInvalid color format. Expected: R,G,B/R,G,B\n");
		return (false);
	}
	if (!parse_first_color(colors, color_1)
		|| !parse_second_color(colors, color_2))
		return (false);
	free_split(colors);
	return (true);
}
