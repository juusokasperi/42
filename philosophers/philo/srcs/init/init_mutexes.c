/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:47:50 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/23 19:29:32 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	destroy_and_free_forks(t_data *data, int i);

/*
	Initializes the mutexes that are shared between threads;
	forks, print_mutex and deaths_mutex.
*/
int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (0);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (destroy_and_free_forks(data, i));
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (destroy_and_free_forks(data, i));
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (destroy_and_free_forks(data, i));
	}
	return (1);
}

static int	destroy_and_free_forks(t_data *data, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&data->forks[i]);
	ft_free((void **)data->forks);
	return (0);
}
