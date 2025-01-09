/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:38:23 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/09 18:03:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_variables(t_info *data)
{
	data->width = 0;
	data->height = 0;
	data->xyz = NULL;
	data->colors = NULL;
	data->highest_z = 0;
	data->lowest_z = 0;
	data->z_scale = 1;
	data->projection = 0;
	data->x_angle = 0;
	data->y_angle = 0;
	data->z_angle = 0;
	data->default_colors = 2;
}

void	calculate_cam(t_info *data)
{
	int	zoom;

	zoom = ft_min(HEIGHT / data->height * 0.7, WIDTH / data->width * 0.7);
	if (zoom != 0)
		data->zoom = zoom;
	else
		data->zoom = 1;
}

void	set_altitude(t_info *data)
{
	if (ft_abs(data->highest_z) + ft_abs(data->lowest_z) > 50)
		data->z_scale = 40;
	else if (ft_abs(data->highest_z) + ft_abs(data->lowest_z) > 25)
		data->z_scale = 60;
	else
		data->z_scale = 80;
}

void	init_data(t_info *data)
{
	data->mlx_ptr = mlx_init(WIDTH + INFO_W, HEIGHT, "FdF jrinta-42", false);
	data->mlx_img = mlx_new_image(data->mlx_ptr, WIDTH + INFO_W, HEIGHT);
	if (!data->mlx_ptr || !data->mlx_img
		|| (mlx_image_to_window(data->mlx_ptr, data->mlx_img, 0, 0) < 0))
		ft_exit_error(4, data);
	clear_image(data);
	draw_instructions(data);
}

void	reset_angles(t_info *data)
{
	data->x_angle = 0;
	data->y_angle = 0;
	data->z_angle = 0;
}
