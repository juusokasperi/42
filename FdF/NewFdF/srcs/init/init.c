/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:38:23 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/06 20:04:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_variables(t_info *data)
{
	data->width = 0;
	data->height = 0;
	data->xyz = NULL;
	data->colors = NULL;
	data->zoom = 50;
	data->highest_z = 0;
	data->lowest_z = 0;
	data->z_scale = 1;
	data->distance = 1;
	data->projection = 1;
	data->x_angle = 0.523599;
	data->y_angle = 0.523599;
	data->default_colors = 1;
	data->rotate = 0;
}

void	set_altitude(t_info *data)
{
	if (ft_abs(data->highest_z) + ft_abs(data->lowest_z) > 50)
		data->z_scale = 2;
	else if (ft_abs(data->highest_z) + ft_abs(data->lowest_z) > 25)
		data->z_scale = 3;
	else
		data->z_scale = 5;
}

int	init_data(t_info *data)
{
	init_variables(data);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "FdF jrinta-42", false);
	data->mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->mlx_ptr || !data->mlx_img
		|| (mlx_image_to_window(data->mlx_ptr, data->mlx_img, 0, 0) < 0))
	{
		free(data);
		return (0);
	}
	clear_image(data);
	draw_instructions(data);
	return (1);
}
