/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:11:59 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/10 23:12:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *y, int *z, t_info *data)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(data->x_angle)
		- *z * sin(data->x_angle);
	*z = prev_y * sin(data->x_angle) + *z * cos(data->x_angle);
}

void	rotate_y(int *x, int *z, t_info *data)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(data->y_angle) + *z * sin(data->y_angle);
	*z = *z * cos(data->y_angle) - prev_x * sin(data->y_angle);
}

void	rotate_z(int *x, int *y, t_info *data)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(data->z_angle) - *y * sin(data->z_angle);
	*y = prev_x * sin(data->z_angle) + *y * cos(data->z_angle);
}
