/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:00:43 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/07 18:24:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw(t_bresenham *line, t_info *data);
static void	prepare_line(int x, int y, int x_or_y, t_info *data);

void	draw_lines(t_info *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x + 1 < data->width)
				prepare_line(x, y, 1, data);
			if (y + 1 < data->height)
				prepare_line(x, y, 0, data);
			x++;
		}
		y++;
	}
}

static void	set_xy(t_bresenham *line, int x, int y, int x_or_y)
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

static void	prepare_line(int x, int y, int x_or_y, t_info *data)
{
	t_bresenham	line;

	set_xy(&line, x, y, x_or_y);
	line.z = data->xyz[line.y][line.x];
	line.z1 = data->xyz[line.y1][line.x1];
	set_colors(&line, data);
	zoom(&line, data);
	set_projection(&line, data);
	shift(&line, data);
	if (((line.x >= 0 || line.x1 >= 0) || (line.y >= 0 || line.y1 >= 0))
		&& ((line.x < WIDTH || line.x1 < WIDTH) || (line.y < HEIGHT && line.y1 < HEIGHT)))
	{
		calculate_bresenham(&line);
		draw(&line, data);
	}
}

static float	calculate_fraction(t_bresenham *line)
{
	int dx;
	int dy;

	dx = line->x1 - line->start_x;
	dy = line->y1 - line->start_y;
	if (ft_abs(dx) > ft_abs(dy) && dx != 0)
		return ((float)line->x - line->start_x) / (float)(dx);
	else if (dy != 0)
		return ((float)line->y - line->start_y) / (float)(dy);
	return (0);
}
uint32_t	interpolate_color(t_bresenham *line)
{
	t_color			c_1;
	t_color			c_2;
	t_color			res;
	t_interpolate	fr;

	fr.f = calculate_fraction(line);
	c_1.r = (line->color_1 >> 24) & 0xFF;
	c_1.g = (line->color_1 >> 16) & 0xFF;
	c_1.b = (line->color_1 >> 8) & 0xFF;

	c_2.r = (line->color_2 >> 24) & 0xFF;
	c_2.g = (line->color_2 >> 16) & 0xFF;
	c_2.b = (line->color_2 >> 8) & 0xFF;

	fr.r = (1 - fr.f) * (c_1.r / 255.0f) + fr.f * (c_2.r / 255.0f);
	fr.g = (1 - fr.f) * (c_1.g / 255.0f) + fr.f * (c_2.g / 255.0f);
	fr.b = (1 - fr.f) * (c_1.b / 255.0f) + fr.f * (c_2.b / 255.0f);

	res.r = (uint8_t)(255 * fr.r);
	res.g = (uint8_t)(255 * fr.g);
	res.b = (uint8_t)(255 * fr.b);

	return ((res.r << 24) | (res.g << 16) | (res.b << 8) | 0xFF);
}

static int	within_bounds(t_bresenham *line)
{
	return (line->x >= 0 && line->x < WIDTH
		&& line->y >= 0 && line->y < HEIGHT);
}

static void	draw(t_bresenham *line, t_info *data)
{
	while (line->x != line->x1 || line->y != line->y1)
	{
		if (within_bounds(line))
			mlx_put_pixel(data->mlx_img, line->x, line->y, interpolate_color(line));
		line->err_2 = 2 * line->err;
		if (line->err_2 >= line->diff_y)
		{
			line->err += line->diff_y;
			line->x += line->step_x;
		}
		if (line->err_2 <= line->diff_x)
		{
			line->err += line->diff_x;
			line->y += line->step_y;
		}
	}
}
