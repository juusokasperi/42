/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:05:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/12 17:46:57 by jrinta-          ###   ########.fr       */
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

// Zooms to the center of the printed wireframe model.
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
}

// Shifts by x,y or if both at 0, centers the wireframe model.
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
		isometric(&line->x, &line->y, line->z, data);
		isometric(&line->x1, &line->y1, line->z1, data);
	}
	else if (data->projection >= 1 && data->projection <= 3)
	{
		orthographic(&line->x, &line->y, line->z, data);
		orthographic(&line->x1, &line->y1, line->z1, data);
	}
	else if (data->projection == 4)
	{
		parallel(&line->x, &line->y, line->z, data);
		parallel(&line->x1, &line->y1, line->z1, data);
	}
	else
	{
		conic(&line->x, &line->y, line->z, data);
		conic(&line->x1, &line->y1, line->z1, data);
	}
}
