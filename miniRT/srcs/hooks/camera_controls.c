/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:04:59 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/13 20:15:31 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_cam_controls	init_cam_controls(void)
{
	t_cam_controls	controls;

	controls.move_speed = 0.5f;
	controls.rotate_speed = 0.05f;
	return (controls);
}

void	update_camera(t_data *data)
{
	fill_black(data);
	raycast(data);
}

void	print_controls(void)
{
	ft_printf("\nCamera Controls:\n");
	ft_printf("Move:\n");
	ft_printf("  W: Forward\n");
	ft_printf("  S: Backward\n");
	ft_printf("  A: Left\n");
	ft_printf("  D: Right\n");
	ft_printf("  Q: Up\n");
	ft_printf("  E: Down\n");
	ft_printf("Rotate:\n");
	ft_printf("  Up Arrow: Look up\n");
	ft_printf("  Down Arrow: Look down\n");
	ft_printf("  Left Arrow: Turn left\n");
	ft_printf("  Right Arrow: Turn right\n");
	ft_printf("Other:\n");
	ft_printf("  ESC: Quit\n");
}

void	loop_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
	{
		cleanup_data(data);
		mlx_terminate(data->mlx_ptr);
		exit(0);
	}
	handle_camera_movement(data);
	handle_camera_rotation(data);
	if (data->should_update == true)
		update_camera(data);
	data->should_update = false;
}
