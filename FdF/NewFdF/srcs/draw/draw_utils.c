/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:00:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/07 13:11:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_line(t_bresenham *line, int x_or_y, t_info *data)
{
	if (x_or_y == 1)
	{
		line->x1 = line->x + 1;
		line->y1 = line->y;
	}
	else
	{
		line->x1 = line->x;
		line->y1 = line->y + 1;
	}
	line->z = data->xyz[line->y][line->x];
	line->z1 = data->xyz[line->y1][line->x1];
	set_colors(line, data);
	zoom(line, data);
	set_projection(line, data);
	shift(line, data);
	line->start_x = line->x;
	line->start_y = line->y;
	line->diff_x = ft_abs(line->x1 - line->x);
	line->diff_y = -(ft_abs(line->y1 - line->y));
	line->err = line->diff_x + line->diff_y;
	calculate_steps(line);
	line->max = ft_max(ft_abs(line->step_x), ft_abs(line->step_y));
}

void	parallel(int *x, int *y, int z, t_info *data)
{
	*x = round(*x + data->distance * z * cos(data->x_angle));
	*y = round(*y + data->distance * z * sin(data->y_angle));
}

void	isometric(int *x, int *y, int z, t_info *data)
{
	int	new_x;
	int	new_y;

	new_x = round((*x - *y) * cos(data->x_angle));
	new_y = round((*x + *y) * sin(data->y_angle) - ((z * data->z_scale)));
	*x = new_x;
	*y = new_y;
}


/*
static void	apply_zoom(t_draw *info, float zoom);
static void	calculate_steps(t_draw *info, t_info *data);
static void	set_colors(t_draw *info, t_info *data);

void	init_info(t_draw *info, t_info *data)
{
	info->z1 = data->xyz[(int)info->y1][(int)info->x1];
	info->z2 = data->xyz[(int)info->y2][(int)info->x2];
	set_colors(info, data);
	apply_zoom(info, data->zoom);
	calculate_steps(info, data);
}

void	set_x_y(float x, float y, t_draw *info, int x_or_y)
{
	info->x1 = x;
	info->y1 = y;
	if (x_or_y == 0)
	{
		info->x2 = x + 1;
		info->y2 = y;
	}
	else
	{
		info->x2 = x;
		info->y2 = y + 1;
	}
}

static void	set_colors(t_draw *info, t_info *data)
{
	if (data->default_colors)
	{
		if (info->z1 > 0)
			info->color_1 = RED;
		else if (info->z1 < 0)
			info->color_1 = BLUE;
		else
			info->color_1 = WHITE;
		if (info->z2 > 0)
			info->color_2 = RED;
		else if (info->z2 < 0)
			info->color_2 = BLUE;
		else
			info->color_2 = WHITE;
	}
	else
	{
		info->color_1 = data->colors[(int)info->y1][(int)info->x1];
		info->color_2 = data->colors[(int)info->y2][(int)info->x2];
	}
}

static void	apply_zoom(t_draw *info, float zoom)
{
	info->x1 *= zoom;
	info->y1 *= zoom;
	info->x2 *= zoom;
	info->y2 *= zoom;
}

static void	calculate_steps(t_draw *info, t_info *data)
{
	if (data->projection == 1)
	{
		isometric(&info->x1, &info->y1, info->z1, data);
		isometric(&info->x2, &info->y2, info->z2, data);
	}
	else
	{
		parallel(&info->x1, &info->y1, info->z1, data);
		parallel(&info->x2, &info->y2, info->z2, data);
	}
	info->x1 += data->shift_x;
	info->y1 += data->shift_y;
	info->x2 += data->shift_x;
	info->y2 += data->shift_y;
	info->x_step = info->x2 - info->x1;
	info->y_step = info->y2 - info->y1;
	if (d_abs(info->x_step) > d_abs(info->y_step))
		info->max = d_abs(info->x_step);
	else
		info->max = d_abs(info->y_step);
	info->x_step /= info->max;
	info->y_step /= info->max;
	info->fraction = 0.0;
}
*/
