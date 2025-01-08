/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:00:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/08 13:16:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(int *y, int *z, t_info *data);
static void	rotate_y(int *x, int *z, t_info *data);
static void	rotate_z(int *x, int *y, t_info *data);

void	orthographic(int *x, int *y, int z, t_info *data)
{
	int	scaled_z;

	scaled_z = (z * data->z_scale * data->zoom) / HEIGHT;
	if (data->projection == 2)
		data->x_angle = 1.570796;
	else if (data->projection == 3)
	{
		data->y_angle = 1.570796;
		data->z_angle = -1.570796;
	}
	rotate_x(y, &scaled_z, data);
	rotate_y(x, &scaled_z, data);
	rotate_z(x, y, data);
}

void	isometric(int *x, int *y, int *z, t_info *data)
{
	int	new_x;
	int	new_y;
	int	scaled_z;

	scaled_z = (*z * data->z_scale * data->zoom) / HEIGHT;
	rotate_x(y, &scaled_z, data);
	rotate_y(x, &scaled_z, data);
	rotate_z(x, y, data);
	new_x = (*x - *y) * cos(0.523599);
	new_y = (*x + *y) * sin(0.523599) - scaled_z;
	*x = new_x;
	*y = new_y;
}

static void	rotate_x(int *y, int *z, t_info *data)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(data->x_angle)
		- *z * sin(data->x_angle);
	*z = prev_y * sin(data->x_angle) + *z * cos(data->x_angle);
}

static void	rotate_y(int *x, int *z, t_info *data)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(data->y_angle) + *z * sin(data->y_angle);
	*z = *z * cos(data->y_angle) - prev_x * sin(data->y_angle);
}

static void	rotate_z(int *x, int *y, t_info *data)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(data->z_angle) - *y * sin(data->z_angle);
	*y = prev_x * sin(data->z_angle) + *y * cos(data->z_angle);
}
