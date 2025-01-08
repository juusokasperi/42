/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:31:09 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/08 11:18:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	shift_values(int *coord);
static void	handle_coordinates(t_info *data, int *coord);

void	calculate_position(t_info *data)
{
	int	coord[5];

	handle_coordinates(data, coord);
	data->zoom = fmin((WIDTH * 0.8) / (coord[RIGHT] - coord[LEFT]),
			(HEIGHT * 0.8) / (coord[BOTTOM] - coord[TOP]));
	data->zoom = ft_abs(data->zoom);
	data->shift_x = (WIDTH / 2) - (coord[CENTER_X] * data->zoom);
	data->shift_y = (HEIGHT / 2)
		- ((coord[TOP] + coord[BOTTOM]) / 2 * data->zoom);
}

static void	handle_coordinates(t_info *data, int *coord)
{
	coord[LEFT] = 0;
	coord[TOP] = 0;
	coord[RIGHT] = data->width - 1;
	coord[BOTTOM] = data->height - 1;
	if (data->projection == 0)
	{
		isometric(&coord[LEFT], &coord[TOP], &data->xyz[0][0], data);
		isometric(&coord[RIGHT], &coord[BOTTOM],
			&data->xyz[(int)coord[BOTTOM]][(int)coord[RIGHT]], data);
	}
	else
	{
		orthographic(&coord[LEFT], &coord[TOP], data->xyz[0][0], data);
		orthographic(&coord[RIGHT], &coord[BOTTOM],
			data->xyz[(int)coord[BOTTOM]][(int)coord[RIGHT]], data);
	}
	coord[CENTER_X] = (coord[LEFT] + coord[RIGHT]) / 2;
	shift_values(coord);
}

static void	shift_values(int *coord)
{
	float	temp;

	if (coord[TOP] < 0)
	{
		coord[BOTTOM] += -(coord[TOP]);
		coord[TOP] = 0;
	}
	if (coord[LEFT] < 0)
	{
		coord[RIGHT] += -(coord[LEFT]);
		coord[LEFT] = 0;
	}
	if (coord[RIGHT] < 0)
	{
		coord[LEFT] += -(coord[RIGHT]);
		coord[RIGHT] = 0;
	}
	if (coord[RIGHT] < coord[LEFT])
	{
		temp = coord[RIGHT];
		coord[RIGHT] = coord[LEFT];
		coord[LEFT] = temp;
	}
}
