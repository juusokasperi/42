/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:31:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/23 22:10:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	shift_values(double *t, double *b, double *l, double *r);

void	calculate_position(t_info *data)
{
	double	left;
	double	right;
	double	top;
	double	bottom;

	left = 0;
	top = 0;
	right = data->width - 1;
	bottom = data->height - 1;
	if (data->projection == 1)
	{
		isometric(&left, &top, data->xyz[0][0], data);
		isometric(&right, &bottom, data->xyz[(int)bottom][(int)right], data);
	}
	else
	{
		parallel(&left, &top, data);
		parallel(&right, &bottom, data);
	}
	data->zoom = fmin((WIDTH * 0.8) / (right - left),
			(HEIGHT * 0.8) / (bottom - top));
	if (top < 0 || left < 0)
		shift_values(&top, &bottom, &left, &right);
	data->shift_x = (WIDTH / 2) - ((left + right) / 2 * data->zoom);
	data->shift_y = (HEIGHT / 2) - ((top + bottom) / 2 * data->zoom);
}

static void	shift_values(double *t, double *b, double *l, double *r)
{
	if (*t < 0)
	{
		*t += -(*t);
		*b += (*t);
	}
	if (*l < 0)
	{
		*l += -(*l);
		*r += (*l);
	}
}
