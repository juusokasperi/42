/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:18:41 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/24 14:41:40 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	pthread_create_failed(t_data *data, int i);

/*
	Creates the threads. In case of an error, sets data.error flag to 1 and
	joins the threads that were created up to that point.

	Upon successful creation of threads, sets the simulation start_time and
	unlocks death_mutex, which philosophers are waiting for and simulation
	begins.
*/
int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->death_mutex);
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
			return (pthread_create_failed(data, i));
	}
	data->start_time = get_time_ms();
	pthread_mutex_unlock(&data->death_mutex);
	return (1);
}

static int	pthread_create_failed(t_data *data, int i)
{
	int	j;

	printf("%sERROR:%s pthread_create failed for philo[%d]\n",
		TRED, TRESET, i);
	data->error = 1;
	pthread_mutex_unlock(&data->death_mutex);
	j = -1;
	while (++j < i)
	{
		if (pthread_join(data->philos[j].thread, NULL) != 0)
		{
			printf("%sERROR:%s pthread_join failed for philo[%d]\n",
				TRED, TRESET, j);
		}
	}
	cleanup_mutexes(data);
	ft_free((void **)&data->philos);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("%sError:%s pthread_join failed for philo[%d]\n",
				TRED, TRESET, i);
			error = 1;
		}
	}
	if (error)
	{
		cleanup_mutexes(data);
		ft_free((void **)&data->philos);
		return (0);
	}
	return (1);
}

void	wait_for_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->death_mutex);
}
