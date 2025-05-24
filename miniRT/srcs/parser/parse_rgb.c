/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:47:20 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/19 23:46:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	validate_rgb_components(char **parts, char *str)
{
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		printf("Error\nRGB color needs exactly 3 components: %s\n", str);
		free_split(parts);
		return (false);
	}
	return (true);
}

static bool	validate_rgb_range(t_rgb *color)
{
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
	{
		printf("Error\nRGB values must be between 0 and 255\n");
		return (false);
	}
	return (true);
}

static bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_rgb(char *str, t_rgb *color)
{
	char	**parts;

	if (!str || !color)
		return (false);
	parts = ft_split(str, ',');
	if (!validate_rgb_components(parts, str))
		return (false);
	if (!is_valid_number(parts[0]) || !is_valid_number(parts[1])
		|| !is_valid_number(parts[2]))
	{
		printf("Error\nRGB values must be numeric: %s\n", str);
		free_split(parts);
		return (false);
	}
	color->r = ft_atoi(parts[0]);
	color->g = ft_atoi(parts[1]);
	color->b = ft_atoi(parts[2]);
	free_split(parts);
	if (!validate_rgb_range(color))
		return (false);
	return (true);
}
