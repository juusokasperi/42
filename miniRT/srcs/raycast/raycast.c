/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:43:14 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/18 13:28:36 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	raycast(t_data *data)
{
	int			x;
	int			y;
	float		t;
	t_ray		ray;
	t_object	closest;

	data->bvh = init_bvh(data);
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			closest.type = NONE;
			ray = get_ray_for_px(data, x, y);
			t = find_closest_intersection(ray, data, &closest);
			if (closest.type != NONE)
				mlx_put_pixel(data->mlx_img, x, y,
					rgb_to_uint(calculate_color(data, closest, ray, t)));
		}
	}
	destroy_bvh(&data->bvh);
}
