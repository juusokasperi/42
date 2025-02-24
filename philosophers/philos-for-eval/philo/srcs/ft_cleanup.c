/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:59:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/24 12:06:05 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_meals_eaten(t_data *data);

int	ft_cleanup(t_data *data)
{
	int		philo_died;
	int		ate_enough_times;

	philo_died = data->philo_died;
	if (data)
		cleanup_mutexes(data);
	ate_enough_times = check_meals_eaten(data);
	if (data->philos)
		ft_free((void **)&data->philos);
	if (data->error)
		return (ft_error("Write call failed in a thread."));
	if (ate_enough_times == 0 && philo_died)
		return (1);
	else
		return (0);
}

static int	check_meals_eaten(t_data *data)
{
	int	i;

	if (data->meals_to_eat == -1)
		return (0);
	i = -1;
	while (++i < data->philo_count)
	{
		if (data->philos[i].meals_ate < data->meals_to_eat)
			return (0);
	}
	return (1);
}

void	cleanup_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->forks[i]);
		if (data->meals_to_eat != -1)
			pthread_mutex_destroy(&data->philos[i].done_mutex);
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	if (data->forks)
		ft_free((void **)&data->forks);
}
