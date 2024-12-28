/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:25:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/28 18:57:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_position(t_info *data);
static void	handle_shift(mlx_key_data_t keydata, t_info *data);
static void	handle_changes(mlx_key_data_t keydata, t_info *data);

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_info	*data;

	data = (t_info *)param;
	handle_shift(keydata, data);
	handle_changes(keydata, data);
	clear_image(data);
	draw_instructions(data);
	draw_lines(data);
	if (keydata.key == 256 && keydata.action == MLX_RELEASE)
	{
		mlx_terminate(data->mlx_ptr);
		ft_exit(data);
	}
}

static void	update_position(t_info *data)
{
	if (data->keys.up)
		data->shift_y -= 10;
	if (data->keys.down)
		data->shift_y += 10;
	if (data->keys.left)
		data->shift_x -= 10;
	if (data->keys.right)
		data->shift_x += 10;
}

static void	handle_shift(mlx_key_data_t keydata, t_info *data)
{
	if (keydata.key == 265 && keydata.action != MLX_RELEASE)
		data->keys.up = 1;
	if (keydata.key == 265 && keydata.action == MLX_RELEASE)
		data->keys.up = 0;
	if (keydata.key == 264 && keydata.action != MLX_RELEASE)
		data->keys.down = 1;
	if (keydata.key == 264 && keydata.action == MLX_RELEASE)
		data->keys.down = 0;
	if (keydata.key == 263 && keydata.action != MLX_RELEASE)
		data->keys.left = 1;
	if (keydata.key == 263 && keydata.action == MLX_RELEASE)
		data->keys.left = 0;
	if (keydata.key == 262 && keydata.action != MLX_RELEASE)
		data->keys.right = 1;
	if (keydata.key == 262 && keydata.action == MLX_RELEASE)
		data->keys.right = 0;
	update_position(data);
}

static void	handle_projection(t_info *data)
{
	if (data->projection == 1)
		data->projection = 0;
	else
		data->projection = 1;
	data->rotate = 0;
	data->angle = 0.523599;
	set_altitude(data);
	calculate_position(data);
}

/* **************************************************** */
/* Distance (parallel projection): 73 = i, 79 = o		*/
/* Zoom: 90 = z, 88 = x									*/
/* Z_scale (altitude): 81 = q, 87 = w					*/
/* Angle: 65 = a, 83 = s								*/
/* Rotate: 82 = r, 84 = t								*/
/* Shift: 265 = up, 264 = down, 263 = left, 262 = right	*/
/* **************************************************** */

static void	handle_changes(mlx_key_data_t keydata, t_info *data)
{
	if (keydata.key == 73 && keydata.action != MLX_RELEASE
		&& data->distance != 0)
		data->distance -= 0.5;
	if (keydata.key == 79 && keydata.action != MLX_RELEASE)
		data->distance += 0.5;
	if (keydata.key == 90 && keydata.action != MLX_RELEASE)
		data->zoom += 0.35;
	if (keydata.key == 88 && keydata.action != MLX_RELEASE)
		data->zoom -= 0.35;
	if (keydata.key == 81 && keydata.action != MLX_RELEASE)
		data->z_scale += 0.5;
	if (keydata.key == 87 && keydata.action != MLX_RELEASE)
		data->z_scale -= 0.5;
	if (keydata.key == 65 && keydata.action != MLX_RELEASE)
		data->angle -= 0.005;
	if (keydata.key == 83 && keydata.action != MLX_RELEASE)
		data->angle += 0.005;
	if (keydata.key == 82 && keydata.action != MLX_RELEASE)
		data->rotate += 0.05;
	if (keydata.key == 84 && keydata.action != MLX_RELEASE)
		data->rotate -= 0.05;
	if (keydata.key == 75 && keydata.action != MLX_RELEASE)
		handle_projection(data);
}
