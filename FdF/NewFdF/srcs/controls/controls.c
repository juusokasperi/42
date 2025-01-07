/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:25:03 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/07 19:00:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/time.h>
#include <stdio.h>

static void	handle_shift(t_info *data);
static void	handle_changes(t_info *data);

void	key_hook(void *param)
{
	t_info	*data;
	struct timeval	stop, start;

	gettimeofday(&start, NULL);
	data = (t_info *)param;
	handle_shift(data);
	handle_changes(data);
	clear_image(data);
	draw_lines(data);
	gettimeofday(&stop, NULL);
	printf("%lu ms\n", ((stop.tv_usec - start.tv_usec)));
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
	{
		mlx_terminate(data->mlx_ptr);
		ft_exit(data);
	}
}

static void	handle_shift(t_info *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_UP))
		data->shift_y -= 10;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_DOWN))
		data->shift_y += 10;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		data->shift_x -= 10;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		data->shift_x += 10;
}

static void	handle_projection(t_info *data)
{
	if (data->projection == 1)
		data->projection = 0;
	else
		data->projection = 1;
	data->distance = 1;
	data->x_angle = 0.523599;
	data->y_angle = 0.523599;
	data->z_angle = 0.523599;
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

static void	handle_changes(t_info *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_I) && data->distance > 0)
		data->distance -= 1;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_O))
		data->distance += 1;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_X))
		data->zoom += 1;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_Z) && data->zoom > 1)
		data->zoom -= 1;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		data->z_scale += 20;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_Q))
		data->z_scale -= 20;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
		data->x_angle -= 0.005;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		data->x_angle += 0.005;
//	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_R))
//		data->rotate += 0.05;
//	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_T))
//		data->rotate -= 0.05;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_K))
		handle_projection(data);
}
