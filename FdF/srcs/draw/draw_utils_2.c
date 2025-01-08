/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:07:44 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/08 12:08:23 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_xy(t_bresenham *line, int x, int y, int x_or_y)
{
	line->x = x;
	line->y = y;
	line->x1 = x;
	line->y1 = y;
	if (x_or_y == 1)
		line->x1++;
	else
		line->y1++;
}

static int	calculate_fraction(t_bresenham *line)
{
	int	dx;
	int	dy;
	int	fraction;

	dx = line->x1 - line->start_x;
	dy = line->y1 - line->start_y;
	if (ft_abs(dx) > ft_abs(dy) && dx != 0)
		fraction = ((line->x - line->start_x) * 255) / dx;
	else if (dy != 0)
		fraction = ((line->y - line->start_y) * 255) / dy;
	else
		fraction = 0;
	return (fraction);
}

uint32_t	interpolate_color(t_bresenham *line)
{
	t_color			c_1;
	t_color			c_2;
	t_color			res;
	int				fraction;

	fraction = calculate_fraction(line);
	c_1.r = (line->color_1 >> 24) & 0xFF;
	c_1.g = (line->color_1 >> 16) & 0xFF;
	c_1.b = (line->color_1 >> 8) & 0xFF;
	c_2.r = (line->color_2 >> 24) & 0xFF;
	c_2.g = (line->color_2 >> 16) & 0xFF;
	c_2.b = (line->color_2 >> 8) & 0xFF;
	res.r = ((255 - fraction) * c_1.r + fraction * c_2.r) >> 8;
	res.g = ((255 - fraction) * c_1.g + fraction * c_2.g) >> 8;
	res.b = ((255 - fraction) * c_1.b + fraction * c_2.b) >> 8;
	return ((res.r << 24) | (res.g << 16) | (res.b << 8) | 0xFF);
}
