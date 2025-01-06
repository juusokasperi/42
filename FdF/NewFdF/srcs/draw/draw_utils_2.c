/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:05:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/06 20:09:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_bresenham *line, t_info *data)
{
	line->x *= data->zoom;
	line->y *= data->zoom;
	line->x1 *= data->zoom;
	line->y1 *= data->zoom;
}

void	calculate_steps(t_bresenham *line)
{
	if (line->y < line->y1)
		line->step_y = 1;
	else
		line->step_y = -1;
	if (line->x < line->x1)
		line->step_x = 1;
	else
		line->step_x = -1;
}

void	shift(t_bresenham *line, t_info *data)
{
	line->x += data->shift_x;
	line->x1 += data->shift_x;
	line->y += data->shift_y;
	line->y1 += data->shift_y;
}

void	set_projection(t_bresenham *line, t_info *data)
{
	if (data->projection == 1)
	{
		isometric(&line->x, &line->y, line->z, data);
		isometric(&line->x1, &line->y1, line->z1, data);
	}
	else
	{
		parallel(&line->x, &line->y, line->z, data);
		parallel(&line->x1, &line->y1, line->z1, data);
	}
}

void	set_colors(t_bresenham *line, t_info *data)
{
	if (data->default_colors)
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
	}
	else
	{
		line->color_1 = data->colors[line->y][line->x];
		line->color_2 = data->colors[line->y1][line->x1];
	}
}
