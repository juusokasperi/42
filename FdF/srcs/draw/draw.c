/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:00:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/18 15:50:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t	interpolate_color(t_draw *info);
static void		draw(double x, double y, t_info *data, int x_or_y);

void	draw_lines(t_info *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x + 1 < data->width)
				draw(x, y, data, 0);
			if (y + 1 < data->height)
				draw(x, y, data, 1);
			x++;
		}
		y++;
	}
}

static void	draw(double x, double y, t_info *data, int x_or_y)
{
	t_draw	*info;

	info = (t_draw *)malloc(sizeof(t_draw));
	if (!info)
		ft_exit_error(3, data);
	set_x_y(x, y, info, x_or_y);
	init_info(info, data);
	while ((int)(info->x1 - info->x2) || (int)(info->y1 - info->y2))
	{
		if (info->x1 >= 0 && info->x1 < WIDTH
			&& info->y1 >= 0 && info->y1 < HEIGHT)
			mlx_put_pixel(data->mlx_img, info->x1,
				info->y1, interpolate_color(info));
		info->x1 += info->x_step;
		info->y1 += info->y_step;
		info->fraction += 1.0 / info->max;
	}
	if (info->x1 >= 0 && info->x1 < WIDTH
		&& info->y1 >= 0 && info->y1 < HEIGHT
		&& info->x2 >= 0 && info->z2 < WIDTH
		&& info->y2 >= 0 && info->y2 < HEIGHT)
		mlx_put_pixel(data->mlx_img, info->x2, info->y2, info->color_2);
	free(info);
}

static uint32_t	interpolate_color(t_draw *info)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	r = ((info->color_1 >> 24) & 0xFF)
		+ (uint32_t)(((info->color_2 >> 24) & 0xFF)
			- ((info->color_1 >> 24) & 0xFF)) * info->fraction;
	g = ((info->color_1 >> 16) & 0xFF)
		+ (uint32_t)(((info->color_2 >> 16) & 0xFF)
			- ((info->color_1 >> 16) & 0xFF)) * info->fraction;
	b = (info->color_1 >> 8 & 0xFF)
		+ (uint32_t)((info->color_2 >> 8 & 0xFF)
			- (info->color_1 >> 8 & 0xFF)) * info->fraction;
	a = (info->color_1 & 0xFF)
		+ (uint32_t)((info->color_2 & 0xFF)
			- (info->color_1 & 0xFF)) * info->fraction;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
