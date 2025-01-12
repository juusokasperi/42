/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:00:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/12 15:32:42 by jrinta-          ###   ########.fr       */
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
	float angle = 0.785398;
	int	new_x;
	int	new_y;

	z = (z * data->z_scale * data->zoom) / HEIGHT;
	rotate_x(y, &z, data);
	rotate_y(x, &z, data);
	rotate_z(x, y, data);
	new_x = *x - (z * cos(angle));
	new_y = *y - (z * sin(angle));
	*x = new_x;
	*y = new_y;
}

void	conic(int *x, int *y, int z, t_info *data)
{
	float	vanishing_point_z;
	float	scale;
	int		new_x;
	int		new_y;

	vanishing_point_z = 1000.0f;
	z = (z * data->z_scale * data->zoom) / HEIGHT;
	rotate_x(y, &z, data);
	rotate_y(x, &z, data);
	rotate_z(x, y, data);
	if (vanishing_point_z - z < 5)
		scale = vanishing_point_z / 10;
	else
		scale = vanishing_point_z / (vanishing_point_z - z);
	new_x = (*x * scale);
	new_y = (*y * scale);
	*x = new_x;
	*y = new_y;
}
