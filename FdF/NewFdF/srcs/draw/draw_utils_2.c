/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:05:09 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/06 18:00:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
static void	rotate(float *x, float *y, float rotate);
void	isometric(float *x, float *y, int z, t_info *data)
{
	float	previous_x;
	float	previous_y;

	rotate(x, y, data->rotate);
	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(data->angle);
	*y = (previous_x + previous_y) * sin(data->angle) - (z * data->z_scale);
}

void	parallel(float *x, float *y, int z, t_info *data)
{
	rotate(x, y, data->rotate);
	*x = *x + data->distance * z * cos(data->angle);
	*y = *y + data->distance * z * sin(data->angle);
}

static void	rotate(float *x, float *y, float rotate)
{
	float	previous_x;
	float	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(rotate) - previous_y * sin(rotate);
	*y = previous_x * sin(rotate) + previous_y * cos(rotate);
}

float	d_abs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

*/
