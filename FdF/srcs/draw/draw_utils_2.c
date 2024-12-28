/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:05:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/28 18:23:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate(double *x, double *y, double rotate);

void	isometric(double *x, double *y, int z, t_info *data)
{
	double	previous_x;
	double	previous_y;

	rotate(x, y, data->rotate);
	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(data->angle);
	*y = (previous_x + previous_y) * sin(data->angle) - (z * data->z_scale);
}

void	parallel(double *x, double *y, int z, t_info *data)
{
	rotate(x, y, data->rotate);
	*x = *x + data->distance * z * cos(data->angle);
	*y = *y + data->distance * z * sin(data->angle);
}

static void	rotate(double *x, double *y, double rotate)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(rotate) - previous_y * sin(rotate);
	*y = previous_x * sin(rotate) + previous_y * cos(rotate);
}

double	d_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}
