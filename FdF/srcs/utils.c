/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:51:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/13 16:49:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_angles(t_info *data)
{
	data->x_angle = 0;
	data->y_angle = 0;
	data->z_angle = 0;
	if (data->projection == 2)
		data->x_angle = 1.570796;
	else if (data->projection == 3)
	{
		data->y_angle = 1.570796;
		data->z_angle = -1.570796;
	}
}

void	calculate_zoom(t_info *data)
{
	data->zoom = ft_min(HEIGHT / data->height * 0.7, WIDTH / data->width * 0.7);
	if (data->zoom == 0)
		data->zoom = 1;
}

// Calculates a default z_scale based on the total height of the map.
void	set_altitude(t_info *data)
{
	data->z_scale = 80;
	if (ft_abs(data->highest_z) + ft_abs(data->lowest_z) > 50)
		data->z_scale /= 2;
	else if (ft_min(data->height, data->width) > 20)
		data->z_scale *= data->zoom / 2;
}
