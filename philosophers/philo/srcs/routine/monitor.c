/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:08 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/22 14:01:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			philo_died(t_philo *philo, t_data *data);
static int		check_all_ate_enough(t_philo *philos, t_data *data);

void	monitor_routine(t_data *data)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			if (data->meals_to_eat != -1)
			{
				if (data->philos[i].meals_ate < data->meals_to_eat
					&& time_since_meal(&data->philos[i]) >= (size_t)data->time_to_die)
					return (philo_died(&data->philos[i], data));
			}
			else if (time_since_meal(&data->philos[i]) >= (size_t)data->time_to_die)
				return (philo_died(&data->philos[i], data));
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			if (data->meals_to_eat != -1
				&& check_all_ate_enough(data->philos, data))
				return ;
		}
		ft_usleep(10);
	}
	return ;
}

static int	check_all_ate_enough(t_philo *philos, t_data *data)
{
	int	i;
	int	all_ate_enough;

	i = -1;
	all_ate_enough = 1;
	while (all_ate_enough && ++i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (philos[i].meals_ate < data->meals_to_eat)
			all_ate_enough = 0;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
	}
	if (all_ate_enough)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->philo_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	philo_died(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&data->print_mutex);
	if (printf("%zu %d %s\n", time_now(data), philo->id, "died") == -1)
		data->error = 1;
	pthread_mutex_unlock(&data->print_mutex);
	return ;
}
