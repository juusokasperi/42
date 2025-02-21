/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:08 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/21 23:30:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			philo_died(t_philo *philos, t_data *data, int i);
static int		check_all_ate_enough(t_philo *philos, t_data *data);

void	monitor_routine(t_data *data)
{
	int		i;
	size_t	time_since_meal;

	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			check_priority(data->philos, data, i);
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			time_since_meal = get_time_ms() - data->start_time \
				- data->philos[i].last_meal;
			if (time_since_meal >= (size_t)data->time_to_die)
				return (philo_died(data->philos, data, i));
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

void	philo_died(t_philo *philos, t_data *data, int i)
{
	pthread_mutex_lock(&data->death_mutex);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&philos[i].meal_mutex);
	if (print_msg(&philos[i], "died") == -1)
		return ;
	return ;
}
