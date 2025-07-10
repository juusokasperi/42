/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_tile_worker_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:05 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/13 23:56:33 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_bonus.h"

static int	get_next_tile_index(t_thread_context *ctx, int max_tiles)
{
	int	tile_index;

	pthread_mutex_lock(&ctx->tile_mutex);
	tile_index = ctx->next_tile++;
	pthread_mutex_unlock(&ctx->tile_mutex);
	if (tile_index >= max_tiles)
		return (-1);
	return (tile_index);
}

static t_tile	get_tile(int width, int height, int tile_index, int tiles_x)
{
	t_tile	tile;
	int		tile_x;
	int		tile_y;

	tile_x = tile_index % tiles_x;
	tile_y = tile_index / tiles_x;
	tile.start_x = tile_x * TILE_SIZE;
	tile.start_y = tile_y * TILE_SIZE;
	tile.end_x = (tile_x + 1) * TILE_SIZE;
	tile.end_y = (tile_y + 1) * TILE_SIZE;
	if (tile.end_x > width)
		tile.end_x = width;
	if (tile.end_y > height)
		tile.end_y = height;
	return (tile);
}

static int	get_max_tiles(int width, int height, int *tiles_x)
{
	int	tiles_y;

	*tiles_x = (width + TILE_SIZE - 1) / TILE_SIZE;
	tiles_y = (height + TILE_SIZE - 1) / TILE_SIZE;
	return (*tiles_x * tiles_y);
}

static void	raytrace_tile(t_data *data, t_tile tile)
{
	int			x;
	int			y;
	float		t;
	t_ray		ray;
	t_object	closest;

	y = tile.start_y - 1;
	while (++y < tile.end_y)
	{
		x = tile.start_x - 1;
		while (++x < tile.end_x)
		{
			closest.type = NONE;
			ray = get_ray_for_px(data, x, y);
			t = find_closest_intersection(ray, data, &closest);
			if (closest.type != NONE)
				mlx_put_pixel(data->mlx_img, x, y,
					rgb_to_uint(calculate_color(data, closest, ray, t)));
		}
	}
}

void	*thread_tile_worker(void *arg)
{
	t_thread_context	*ctx;
	int					tile_index;
	int					tiles_x;
	int					max_tiles;
	t_tile				tile;

	ctx = (t_thread_context *)arg;
	max_tiles = get_max_tiles(ctx->data->width, ctx->data->height, &tiles_x);
	while (1)
	{
		tile_index = get_next_tile_index(ctx, max_tiles);
		if (tile_index == -1)
			break ;
		tile = get_tile(
				ctx->data->width, ctx->data->height, tile_index, tiles_x);
		raytrace_tile(ctx->data, tile);
	}
	return (NULL);
}
