/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:04:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/08 15:58:29 by jrinta-          ###   ########.fr       */
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
		data->default_colors = !data->default_colors;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_RELEASE)
		handle_projection(data);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_RELEASE)
		reset_angles(data);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		set_altitude(data);
}

static void	handle_projection(t_info *data)
{
	if (data->projection < 3)
		data->projection++;
	else
		data->projection = 0;
	reset_angles(data);
//	calculate_position(data);
}
