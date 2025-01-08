/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:05:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/08 18:10:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_bresenham *line, t_info *data)
{
	line->x = line->x * data->zoom - (data->width / 2) * data->zoom;
	line->y = line->y * data->zoom - (data->height / 2) * data->zoom;
	line->x1 = line->x1 * data->zoom - (data->width / 2) * data->zoom;
	line->y1 = line->y1 * data->zoom - (data->height / 2) * data->zoom;
}

void	calculate_bresenham(t_bresenham *line)
{
	line->start_x = line->x;
	line->start_y = line->y;
	line->diff_x = ft_abs(line->x1 - line->x);
	line->diff_y = -(ft_abs(line->y1 - line->y));
	line->err = line->diff_x + line->diff_y;
	if (line->y < line->y1)
		line->step_y = 1;
	else
		line->step_y = -1;
	if (line->x < line->x1)
		line->step_x = 1;
	else
		line->step_x = -1;
	line->max = ft_max(ft_abs(line->step_x), ft_abs(line->step_y));
}

void	shift(t_bresenham *line, t_info *data)
{
	line->x += data->shift_x + WIDTH / 2;
	line->x1 += data->shift_x + WIDTH / 2;
	line->y += data->shift_y + HEIGHT / 2;
	line->y1 += data->shift_y + HEIGHT / 2;
}

void	set_projection(t_bresenham *line, t_info *data)
{
	if (data->projection == 0)
	{
		isometric(&line->x, &line->y, &line->z, data);
		isometric(&line->x1, &line->y1, &line->z1, data);
	}
	else
	{
		orthographic(&line->x, &line->y, line->z, data);
		orthographic(&line->x1, &line->y1, line->z1, data);
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
