/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:31:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/17 19:15:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (tx < minmax->min_x)
		minmax->min_x = tx;
	if (tx > minmax->max_x)
		minmax->max_x = tx;
	if (ty < minmax->min_y)
		minmax->min_y = ty;
	if (ty > minmax->max_y)
		minmax->max_y = ty;
}

static void	calculate_min_max(t_info *data, t_minmax *minmax)
{
	int		y;
	int		x;
	double	tx;
	double	ty;

	minmax->min_x = WIDTH;
	minmax->max_x = 0;
	minmax->min_y = HEIGHT;
	minmax->max_y = 0;
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

	width_zoom = (0.75 * WIDTH) / (minmax->max_x - minmax->min_x);
	height_zoom = (0.75 * HEIGHT) / (minmax->max_y - minmax->min_y);
	if (width_zoom < height_zoom)
		return (width_zoom);
	return (height_zoom);
}
