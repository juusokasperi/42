/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:00:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/08 20:08:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	f_abs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	draw(float x1, float y1, float x2, float y2, t_info *data)
{
	float	x_step;
	float	y_step;
	int		max;
	int		i;

	i = 0;
	x_step = x2 - x1;
	y_step = y2 - y1;
	if (f_abs(x_step) > f_abs(y_step))
		max = f_abs(x_step);
	else
		max = f_abs(y_step);
	x_step /= max;
	y_step /= max;
	while (i <= max)
	{
		mlx_put_pixel(data->mlx_img, x1, y1, 0xFFFFFF);
		x1 += x_step;
		y1 += y_step;
		i++;
	}
}

/*
void draw(int x1, int y1, int x2, int y2, t_info *data)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_put_pixel(data->mlx_img, x1, y1, 0xFFFFFF); // White color
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}
*/
