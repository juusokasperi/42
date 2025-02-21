/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:18:41 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/21 19:04:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->death_lock);
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
		{
			pthread_mutex_unlock(&data->death_lock);
			cleanup_mutexes(data);
			ft_free((void **)&data->philos);
			return (0);
		}
	}
	data->start_time = get_time_ms();
	pthread_mutex_unlock(&data->death_lock);
	return (1);
}

int	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			cleanup_mutexes(data);
			ft_free((void **)&data->philos);
			return (0);
		}
	}
	return (1);
}

void	wait_for_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->death_lock);
}
