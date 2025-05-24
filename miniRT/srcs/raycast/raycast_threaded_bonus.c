/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_threaded_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:30:45 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/18 13:31:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_bonus.h"
#include <unistd.h>

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

static int	init_thread_context(t_data *data, t_thread_context *ctx,
			pthread_t **threads, int thread_count)
{
	*threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);
	if (!*threads)
	{
		printf("Error\nFailed to allocate memory for threads\n");
		return (0);
	}
	ctx->data = data;
	ctx->thread_count = thread_count;
	ctx->next_tile = 0;
	pthread_mutex_init(&ctx->tile_mutex, NULL);
	return (1);
}

static int	create_threads(pthread_t *threads, t_thread_context *ctx,
		int thread_count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < thread_count)
	{
		if (pthread_create(&threads[i], NULL, thread_tile_worker, ctx))
		{
			printf("Error creating thread %d\n", i);
			j = -1;
			while (++j < i)
			{
				if (pthread_join(threads[j], NULL) != 0)
					printf("Error joining thread %d\n", j);
			}
			return (0);
		}
	}
	return (1);
}

static void	join_and_cleanup(pthread_t *threads, t_thread_context *ctx,
				int thread_count, t_data *data)
{
	int	i;

	i = -1;
	while (++i < thread_count)
	{
		if (pthread_join(threads[i], NULL) != 0)
			printf("Error joining thread %d\n", i);
	}
	free(threads);
	pthread_mutex_destroy(&ctx->tile_mutex);
	destroy_bvh(&data->bvh);
}

void	raycast_threaded(t_data *data, int thread_count)
{
	pthread_t			*threads;
	t_thread_context	ctx;

	data->bvh = init_bvh(data);
	if (!init_thread_context(data, &ctx, &threads, thread_count))
	{
		raycast(data);
		return ;
	}
	if (!create_threads(threads, &ctx, thread_count))
	{
		free(threads);
		pthread_mutex_destroy(&ctx.tile_mutex);
		raycast(data);
		return ;
	}
	join_and_cleanup(threads, &ctx, thread_count, data);
}
