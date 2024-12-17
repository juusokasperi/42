/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .draw_og.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:00:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/17 19:23:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	d_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	rotate(double *x, double *y, double rotate)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(rotate) - previous_y * sin(rotate);
	*y = previous_x * sin(rotate) + previous_y * cos(rotate);
}

static void	parallel(double *x, double *y, t_info *data)
{
	rotate(x, y, data->rotate);
	*x *= cos(data->angle);
	*y *= sin(data->angle);
}

void	isometric(double *x, double *y, int z, t_info *data)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	rotate(x, y, data->rotate);
	*x = (previous_x - previous_y) * cos(data->angle);
	*y = (previous_x + previous_y) * sin(data->angle) - (z * data->z_scale);
}

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
				draw(x, y, x + 1, y, data);
			if (y + 1 < data->height)
				draw(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}

uint32_t	interpolate_color(t_draw *info)
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

void	draw(double x1, double y1, double x2, double y2, t_info *data)
{
	double			x_step;
	double			y_step;
	int				max;
	uint32_t		color;
	uint32_t		color_1;
	uint32_t		color_2;
	int				z1;
	int				z2;
	double			fraction;

	z1 = data->xyz[(int)y1][(int)x1];
	z2 = data->xyz[(int)y2][(int)x2];
	if (data->default_colors)
	{
		if (z1 == 0)
			color_1 = WHITE;
		else if (z1 > 0)
			color_1 = RED;
		else if (z1 < 0)
			color_1 = BLUE;
		if (z2 == 0)
			color_2 = WHITE;
		else if (z2 > 0)
			color_2 = RED;
		else if (z2 < 0)
			color_2 = BLUE;
	}
	else
	{
		color_1 = data->colors[(int)y1][(int)x1];
		color_2 = data->colors[(int)y2][(int)x2];
	}
	x1 *= data->zoom;
	y1 *= data->zoom;
	x2 *= data->zoom;
	y2 *= data->zoom;
	if (data->projection == 1)
	{
		isometric(&x1, &y1, z1, data);
		isometric(&x2, &y2, z2, data);
	}
	else if (data->projection == 2)
	{
		parallel(&x1, &y1, data);
		parallel(&x2, &y2, data);
	}
	x1 += data->shift_x;
	y1 += data->shift_y;
	x2 += data->shift_x;
	y2 += data->shift_y;
	x_step = x2 - x1;
	y_step = y2 - y1;
	if (d_abs(x_step) > d_abs(y_step))
		max = d_abs(x_step);
	else
		max = d_abs(y_step);
	x_step /= max;
	y_step /= max;
	fraction = 0.0;
	while ((int)(x1 - x2) || (int)(y1 - y2))
	{
		if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
		{
			color = interpolate_color(color_1, color_2, fraction);
			mlx_put_pixel(data->mlx_img, x1, y1, color);
		}
		x1 += x_step;
		y1 += y_step;
		fraction += 1.0 / max;
	}
	if (x2 >= 0 && x2 < WIDTH && y2 >= 0 && y2 < HEIGHT)
		mlx_put_pixel(data->mlx_img, x2, y2, color_2);
}
