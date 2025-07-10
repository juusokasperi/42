/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:06:09 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/11 22:05:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	calculate_fraction(t_bresenham *line);
static void	handle_transparency(t_bresenham *line);

void	set_colors(t_bresenham *line, t_info *data)
{
	if (data->default_colors >= 2)
	{
		if (line->z > 0)
			line->color_1 = RED;
		else if (line->z < 0)
			line->color_1 = BLUE;
		else
			line->color_1 = WHITE;
		if (line->z1 > 0)
			line->color_2 = RED;
		else if (line->z1 < 0)
			line->color_2 = BLUE;
		else
			line->color_2 = WHITE;
		if (data->default_colors == 3)
			handle_transparency(line);
	}
	else
	{
		line->color_1 = data->colors[line->y][line->x];
		line->color_2 = data->colors[line->y1][line->x1];
		if (data->default_colors == 1)
			handle_transparency(line);
	}
}

static void	handle_transparency(t_bresenham *line)
{
	if (line->z == 0)
		line->color_1 = TRANSPARENT;
	if (line->z1 == 0)
		line->color_2 = TRANSPARENT;
}

// Calculates the gradient between colors.
// For each pixel we draw in a line, we need to calculate a color.
// For x0,y0 color will be c_1, x1,y1 will be c_2.
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

// When drawing x0,y0 fraction will be 0.
// It increments gradually to 255 at x1,y1.
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
