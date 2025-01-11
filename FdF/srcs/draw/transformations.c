/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:00:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/11 22:45:56 by jrinta-          ###   ########.fr       */
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
