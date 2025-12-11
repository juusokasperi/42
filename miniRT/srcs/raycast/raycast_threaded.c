/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_threaded.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:30:45 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/18 13:31:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <unistd.h>

void	cleanup_thread_pool(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->pool.work_mutex);
	data->pool.stop = true;
	pthread_cond_broadcast(&data->pool.work_cond);
	pthread_mutex_unlock(&data->pool.work_mutex);
	i = -1;
	while (++i < data->pool.thread_count)
		pthread_join(data->pool.threads[i], NULL);
	pthread_mutex_destroy(&data->pool.work_mutex);
	pthread_cond_destroy(&data->pool.work_cond);
	pthread_mutex_destroy(&data->pool.done_mutex);
	pthread_cond_destroy(&data->pool.done_cond);
	pthread_mutex_destroy(&data->ctx.tile_mutex);
}

int	get_system_thread_count(void)
{
	int		thread_count;
	long	nprocs;

	thread_count = NUM_THREADS;
	nprocs = sysconf(_SC_NPROCESSORS_ONLN);
	if (nprocs > 0)
		return ((int)nprocs);
	return (thread_count);
}

static int	create_threads(pthread_t *threads, t_thread_ctx *ctx,
		int thread_count)
{
	int	i;

	i = -1;
	while (++i < thread_count)
	{
		if (pthread_create(&threads[i], NULL, thread_tile_worker, ctx))
		{
			printf("Error creating thread %d\n", i);
			while (--i)
			{
				if (pthread_join(threads[i], NULL) != 0)
					printf("Error joining thread %d\n", i);
			}
			return (0);
		}
	}
	return (1);
}

int	init_thread_pool(t_data *data)
{
	data->pool.thread_count = get_system_thread_count();
	data->ctx.data = data;
	data->ctx.next_tile = 0;
	pthread_mutex_init(&data->ctx.tile_mutex, NULL);
	data->pool.threads = malloc(sizeof(pthread_t) * data->pool.thread_count);
	pthread_mutex_init(&data->pool.work_mutex, NULL);
	pthread_cond_init(&data->pool.work_cond, NULL);
	pthread_mutex_init(&data->pool.done_mutex, NULL);
	pthread_cond_init(&data->pool.done_cond, NULL);
	data->pool.stop = false;
	data->pool.working = false;
	data->pool.frame_id = 0;
	if (!create_threads(data->pool.threads,
			&data->ctx, data->pool.thread_count))
		return (0);
	return (1);
}

void	raycast_threaded(t_data *data)
{
	pthread_mutex_lock(&data->ctx.tile_mutex);
	data->ctx.next_tile = 0;
	pthread_mutex_unlock(&data->ctx.tile_mutex);
	pthread_mutex_lock(&data->pool.done_mutex);
	data->pool.frame_id++;
	data->pool.finished_count = 0;
	pthread_mutex_unlock(&data->pool.done_mutex);
	pthread_mutex_lock(&data->pool.work_mutex);
	data->pool.working = true;
	pthread_cond_broadcast(&data->pool.work_cond);
	pthread_mutex_unlock(&data->pool.work_mutex);
	pthread_mutex_lock(&data->pool.done_mutex);
	while (data->pool.finished_count < data->pool.thread_count)
		pthread_cond_wait(&data->pool.done_cond, &data->pool.done_mutex);
	pthread_mutex_unlock(&data->pool.done_mutex);
}
