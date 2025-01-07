/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:31:09 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/07 19:13:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static void	shift_values(int *coord);
static void	handle_coordinates(t_info *data, int *coord);

void	calculate_position(t_info *data)
{
	int	coord[4];

	handle_coordinates(data, coord);
	data->zoom = fmin((WIDTH * 0.8) / (coord[RIGHT] - coord[LEFT]),
			(HEIGHT * 0.8) / (coord[BOTTOM] - coord[TOP]));
}

static void	handle_coordinates(t_info *data, int *coord)
{
	coord[LEFT] = 0;
	coord[TOP] = 0;
	coord[RIGHT] = data->width - 1;
	coord[BOTTOM] = data->height - 1;
	if (data->projection == 1)
	{
		isometric(&coord[LEFT], &coord[TOP], &data->xyz[0][0], data);
		isometric(&coord[RIGHT], &coord[BOTTOM],
			&data->xyz[(int)coord[BOTTOM]][(int)coord[RIGHT]], data);
	}
	else
	{
		parallel(&coord[LEFT], &coord[TOP], data->xyz[0][0], data);
		parallel(&coord[RIGHT], &coord[BOTTOM],
			data->xyz[(int)coord[BOTTOM]][(int)coord[RIGHT]], data);
	}
//	shift_values(coord);
}

// static void	shift_values(int *coord)
// {
// 	float	temp;

// 	if (coord[TOP] < 0)
// 	{
// 		coord[BOTTOM] += -(coord[TOP]);
// 		coord[TOP] = 0;
// 	}
// 	if (coord[LEFT] < 0)
// 	{
// 		coord[RIGHT] += -(coord[LEFT]);
// 		coord[LEFT] = 0;
// 	}
// 	if (coord[RIGHT] < 0)
// 	{
// 		coord[LEFT] += -(coord[RIGHT]);
// 		coord[RIGHT] = 0;
// 	}
// 	if (coord[RIGHT] < coord[LEFT])
// 	{
// 		temp = coord[RIGHT];
// 		coord[RIGHT] = coord[LEFT];
// 		coord[LEFT] = temp;
// 	}
// }
