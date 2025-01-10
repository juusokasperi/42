/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:00:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/11 00:30:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	orthographic(int *x, int *y, int z, t_info *data)
{
	z = (z * data->z_scale * data->zoom) / HEIGHT;
	if (data->projection == 2)
		data->x_angle = 1.570796;
	else if (data->projection == 3)
	{
		data->y_angle = 1.570796;
		data->z_angle = -1.570796;
	}
	rotate_x(y, &z, data);
	rotate_y(x, &z, data);
	rotate_z(x, y, data);
}

void	perspective(int *x, int *y, int z, t_info *data)
{
	float		fov;
	float		distance;
	long long	temp_x;
	long long	temp_y;

	z = (z * data->z_scale * data->zoom) / HEIGHT;
	rotate_x(y, &z, data);
	rotate_y(x, &z, data);
	rotate_z(x, y, data);
	distance = 1000;
	if (distance - z <= 100)
		z = 100;
	fov = distance / (distance - z);
	temp_x = (*x * fov) + WIDTH / 2;
	temp_y = (*y * fov) + HEIGHT / 2;
	if (temp_x > INT_MAX || temp_x < INT_MIN
		|| temp_y > INT_MAX || temp_y < INT_MIN)
		return;
	*x = temp_x;
	*y = temp_y;
}

void	isometric(int *x, int *y, int z, t_info *data)
{
	int	new_x;
	int	new_y;

	z = (z * data->z_scale * data->zoom) / HEIGHT;
	rotate_x(y, &z, data);
	rotate_y(x, &z, data);
	rotate_z(x, y, data);
	new_x = (*x - *y) * cos(0.523599);
	new_y = (*x + *y) * sin(0.523599) - z;
	*x = new_x;
	*y = new_y;
}
