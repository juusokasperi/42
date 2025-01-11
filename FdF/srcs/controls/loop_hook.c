/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:25:03 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/11 22:52:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_shift(t_info *data);
static void	handle_changes(t_info *data);

void	loop_hook(void *param)
{
	t_info	*data;

	data = (t_info *)param;
	handle_shift(data);
	handle_changes(data);
	clear_image(data);
	draw_lines(data);
}

static void	handle_shift(t_info *data)
{
	int	fast;

	fast = 0;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_KP_0))
		fast = 50;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_UP))
		data->shift_y -= 10 + fast;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_DOWN))
		data->shift_y += 10 + fast;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		data->shift_x -= 10 + fast;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		data->shift_x += 10 + fast;
	fast = 0;
}

static void	handle_changes(t_info *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_X))
		data->zoom += 1;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_Z) && data->zoom > 1)
		data->zoom -= 1;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		data->z_scale += 20;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_Q))
		data->z_scale -= 20;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_1))
		data->x_angle -= 0.05;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_2))
		data->x_angle += 0.05;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_3))
		data->y_angle -= 0.05;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_4))
		data->y_angle += 0.05;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_5))
		data->z_angle -= 0.05;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_6))
		data->z_angle += 0.05;
}
