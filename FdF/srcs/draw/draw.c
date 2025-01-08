/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:00:43 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/08 15:58:30 by jrinta-          ###   ########.fr       */
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
		&& ((line.x < WIDTH || line.x1 < WIDTH)
			|| (line.y < HEIGHT && line.y1 < HEIGHT)))
	{
		calculate_bresenham(&line);
		draw(&line, data);
	}
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
			mlx_put_pixel(data->mlx_img, line->x,
				line->y, interpolate_color(line));
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
