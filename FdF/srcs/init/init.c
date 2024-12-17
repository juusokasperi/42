/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:38:23 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/17 19:11:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_variables(t_info *data)
{
	data->width = 0;
	data->height = 0;
	data->xyz = NULL;
	data->colors = NULL;
	data->zoom = 20;
	data->z_scale = 2.5;
	data->projection = 1;
	data->angle = 0.523599;
	data->default_colors = 1;
	data->rotate = 0;
}

int	init_data(t_info *data)
{
	init_variables(data);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "FdF jrinta-42", true);
	data->mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->mlx_ptr || !data->mlx_img
		|| (mlx_image_to_window(data->mlx_ptr, data->mlx_img, 0, 0) < 0))
	{
		free(data);
		return (0);
	}
	clear_image(data);
	return (1);
}
