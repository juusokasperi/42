/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:00:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/07 19:17:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
static void	rotate_x(int *y, int *z, t_info *data);
static void	rotate_y(int *x, int *z, t_info *data);
static void	rotate_z(int *x, int *y, t_info *data);
*/

void	parallel(int *x, int *y, int z, t_info *data)
{
	*x = round(*x + data->distance * z * cos(data->x_angle));
	*y = round(*y + data->distance * z * sin(data->y_angle));
}

void	isometric(int *x, int *y, int *z, t_info *data)
{
//	rotate_x(y, z, data);
//	rotate_y(x, z, data);
//	rotate_z(x, y, data);
	int	new_x;
	int	new_y;

	new_x = round((*x - *y) * cos(data->x_angle));
	new_y = round((*x + *y) * sin(data->y_angle) - ((*z * data->z_scale * data->zoom) / HEIGHT));
	*x = new_x;
	*y = new_y;
}
/*
static void	rotate_x(int *y, int *z, t_info *data)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(data->x_angle) -
		((*z * data->z_scale * data->zoom) / HEIGHT) * sin(data->x_angle);
	*z = prev_y * sin(data->x_angle) + (((*z * data->z_scale * data->zoom) / HEIGHT) * cos(data->x_angle));
}

static void	rotate_y(int *x, int *z, t_info *data)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(data->y_angle) - ((*z * data->z_scale * data->zoom) / HEIGHT) * sin(data->y_angle);
	*z = prev_x * sin(data->y_angle) + ((*z * data->z_scale * data->zoom) / HEIGHT) * cos(data->y_angle);
}

static void	rotate_z(int *x, int *y, t_info *data)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(data->z_angle) - *y * sin(data->z_angle);
	*y = prev_x * sin(data->z_angle) + *y * cos(data->z_angle);
}

*/
