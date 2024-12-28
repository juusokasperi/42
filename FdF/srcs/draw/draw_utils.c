/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:00:00 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/28 12:11:27 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	apply_zoom(t_draw *info, double zoom);
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

void	set_x_y(double x, double y, t_draw *info, int x_or_y)
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

static void	apply_zoom(t_draw *info, double zoom)
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
