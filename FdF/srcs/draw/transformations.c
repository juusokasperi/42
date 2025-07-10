/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:00:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/13 16:40:17 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	orthographic(int *x, int *y, int z, t_info *data)
{
	z = (z * data->z_scale * data->zoom) / HEIGHT;
	rotate_x(y, &z, data);
	rotate_y(x, &z, data);
	rotate_z(x, y, data);
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

// 0.785398 for 45 degress
void	parallel(int *x, int *y, int z, t_info *data)
{
	z = (z * data->z_scale * data->zoom) / HEIGHT;
	rotate_x(y, &z, data);
	rotate_y(x, &z, data);
	rotate_z(x, y, data);
	*x -= (z * cos(0.785398));
	*y -= (z * sin(0.785398));
}

void	conic(int *x, int *y, int z, t_info *data)
{
	float	vanishing_point_z;
	float	scale;

	vanishing_point_z = 500;
	z = (z * data->z_scale * data->zoom) / HEIGHT;
	rotate_x(y, &z, data);
	rotate_y(x, &z, data);
	rotate_z(x, y, data);
	if (vanishing_point_z - z < 10)
		scale = vanishing_point_z / 10;
	else
		scale = vanishing_point_z / (vanishing_point_z - z);
	*x *= scale;
	*y *= scale;
}
