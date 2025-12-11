/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_tile_worker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:05 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/13 23:56:33 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	get_next_tile_index(t_thread_ctx *ctx, int max_tiles)
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
	uint32_t	color;

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
				color = rgb_to_uint(calculate_color(data, closest, ray, t));
			else
				color = BACKGROUND_COLOR;
			mlx_put_pixel(data->mlx_img, x, y, color);
		}
	}
}

void	*thread_tile_worker(void *arg)
{
	t_thread_ctx		*ctx;
	t_data				*data;
	int					tile_index;
	int					tiles_x;
	int					max_tiles;
	t_tile				tile;
	long				local_frame_id;

	ctx = (t_thread_ctx *)arg;
	data = ctx->data;
	local_frame_id = 0;
	while (1)
	{
		pthread_mutex_lock(&data->pool.work_mutex);
		while ((local_frame_id == data->pool.frame_id || !data->pool.working)
			&& !data->pool.stop)
			pthread_cond_wait(&data->pool.work_cond, &data->pool.work_mutex);
		if (data->pool.stop)
		{
			pthread_mutex_unlock(&data->pool.work_mutex);
			break ;
		}
		local_frame_id = data->pool.frame_id;
		pthread_mutex_unlock(&data->pool.work_mutex);
		max_tiles = get_max_tiles(data->width, data->height, &tiles_x);
		while (1)
		{
			tile_index = get_next_tile_index(ctx, max_tiles);
			if (tile_index == -1)
				break ;
			tile = get_tile(
					ctx->data->width, ctx->data->height, tile_index, tiles_x);
			raytrace_tile(ctx->data, tile);
		}
		pthread_mutex_lock(&data->pool.done_mutex);
		data->pool.finished_count++;
		if (data->pool.finished_count == data->pool.thread_count)
			pthread_cond_signal(&data->pool.done_cond);
		pthread_mutex_unlock(&data->pool.done_mutex);
	}
	return (NULL);
}
