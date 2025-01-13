/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:04:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/13 16:43:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_toggles(mlx_key_data_t keydata, t_info *data);
static void	handle_projection(t_info *data);

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_info	*data;

	data = (t_info *)param;
	handle_toggles(keydata, data);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_terminate(data->mlx_ptr);
		ft_exit(data);
	}
}

static void	handle_toggles(mlx_key_data_t keydata, t_info *data)
{
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_RELEASE)
		data->default_colors = (data->default_colors + 1) % 4;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_RELEASE)
		handle_projection(data);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_RELEASE)
		reset_angles(data);
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_RELEASE)
		set_altitude(data);
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_RELEASE)
	{
		data->shift_x = 0;
		data->shift_y = 0;
		calculate_zoom(data);
	}
}

static void	handle_projection(t_info *data)
{
	data->projection = (data->projection + 1) % 6;
	data->shift_x = 0;
	data->shift_y = 0;
	calculate_zoom(data);
	reset_angles(data);
}
