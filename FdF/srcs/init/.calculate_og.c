/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:31:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/17 20:00:22 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <float.h>

static void		update_min_max(double tx, double ty, t_minmax *minmax);
static void		calculate_min_max(t_info *data, t_minmax *minmax);
static double	calculate_zoom_factor(t_minmax *minmax);

void	calculate_zoom(t_info *data)
{
	t_minmax	minmax;

	calculate_min_max(data, &minmax);
	data->zoom = calculate_zoom_factor(&minmax);
	minmax.min_x *= data->zoom;
	minmax.max_x *= data->zoom;
	minmax.min_y *= data->zoom;
	minmax.max_y *= data->zoom;
	data->shift_x = (WIDTH - (minmax.max_x - minmax.min_x))
		/ 2 - minmax.min_x;
	data->shift_y = ((HEIGHT
				- (minmax.max_y - minmax.min_y)) / 2 - minmax.min_y) / 3;
	if (data->shift_x < 0)
		data->shift_x = 0;
	if (data->shift_y < 0)
		data->shift_y = 0;
}

static void	update_min_max(double tx, double ty, t_minmax *minmax)
{
	if (minmax->min_x > minmax->max_x || minmax->min_y > minmax->max_y)
	{
		minmax->min_x = tx;
		minmax->max_x = tx;
		minmax->min_y = ty;
		minmax->max_y = ty;
	}
	else
	{
		minmax->min_x = fmin(minmax->min_x, tx);
		minmax->max_x = fmax(minmax->max_x, tx);
		minmax->min_y = fmin(minmax->min_y, ty);
		minmax->max_y = fmax(minmax->max_y, ty);
	}
}

static void	calculate_min_max(t_info *data, t_minmax *minmax)
{
	int		y;
	int		x;
	double	tx;
	double	ty;

	minmax->min_x = DBL_MAX;
    minmax->max_x = -DBL_MAX;
    minmax->min_y = DBL_MAX;
    minmax->max_y = -DBL_MAX;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			tx = x;
			ty = y;
			isometric(&tx, &ty, data->xyz[y][x], data);
			update_min_max(tx, ty, minmax);
			x++;
		}
		y++;
	}
}

static double	calculate_zoom_factor(t_minmax *minmax)
{
	double	width_zoom;
	double	height_zoom;
	double	padding;

	padding = 0.9;
	width_zoom = (padding * WIDTH) / (minmax->max_x - minmax->min_x);
	height_zoom = (padding * HEIGHT) / (minmax->max_y - minmax->min_y);
	return fmin(width_zoom, height_zoom);
}
