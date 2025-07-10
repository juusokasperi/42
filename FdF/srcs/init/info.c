/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:32:03 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/11 22:51:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_info_bg(t_info *data);
static void	draw_info_box(t_info *data);

void	draw_instructions(t_info *data)
{
	int				x;
	int				y;

	x = WIDTH + INFO_W * 0.15;
	y = HEIGHT * 0.05;
	draw_info_bg(data);
	draw_info_box(data);
	mlx_put_string(data->mlx_ptr, "CONTROLS", x, y + 20);
	mlx_put_string(data->mlx_ptr, "arrows: move", x, y + 60);
	mlx_put_string(data->mlx_ptr, "1/2: rotate x", x, y + 80);
	mlx_put_string(data->mlx_ptr, "3/4: rotate y", x, y + 100);
	mlx_put_string(data->mlx_ptr, "5/6: rotate z", x, y + 120);
	mlx_put_string(data->mlx_ptr, "q/w: z-scale", x, y + 140);
	mlx_put_string(data->mlx_ptr, "r: reset rotation", x, y + 160);
	mlx_put_string(data->mlx_ptr, "t: reset z", x, y + 180);
	mlx_put_string(data->mlx_ptr, "y: center", x, y + 200);
	mlx_put_string(data->mlx_ptr, "z/x: zoom", x, y + 220);
	mlx_put_string(data->mlx_ptr, "c: colors", x, y + 240);
	mlx_put_string(data->mlx_ptr, "p: projection", x, y + 260);
	mlx_put_string(data->mlx_ptr, "esc: exit", x, y + 280);
}

static void	draw_info_bg(t_info *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = WIDTH - 1;
		while (++x < WIDTH + INFO_W)
		{
			if (x == WIDTH || x == WIDTH + 5)
				mlx_put_pixel(data->mlx_img, x, y, 0xBABABAFF);
			else
				mlx_put_pixel(data->mlx_img, x, y, BLACK);
		}
	}
}

static void	draw_info_box(t_info *data)
{
	int	x;
	int	y;

	y = (HEIGHT * 0.05) - 1;
	while (++y < HEIGHT * 0.05 + 320)
	{
		x = WIDTH + (INFO_W * 0.1) - 1;
		while (++x < WIDTH + (INFO_W * 0.9))
		{
			if (y == (int)(HEIGHT * 0.05) || y == (int)(HEIGHT * 0.05 + 5)
				|| x == (int)(WIDTH + INFO_W * 0.1)
				|| x == (int)(WIDTH + INFO_W * 0.1 + 5)
				|| y == (int)(HEIGHT * 0.05 + 320)
				|| y == (int)(HEIGHT * 0.05 + 315)
				|| x == (int)(WIDTH + INFO_W * 0.9)
				|| x == (int)(WIDTH + INFO_W * 0.9 - 5))
				mlx_put_pixel(data->mlx_img, x, y, 0xBABABAFF);
			else
				mlx_put_pixel(data->mlx_img, x, y, 0x0000CCFF);
		}
	}
}
