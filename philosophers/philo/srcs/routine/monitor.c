/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:08 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/24 11:48:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		check_all_ate_enough(t_philo *philos, t_data *data);
static void		philo_died(t_philo *philo, t_data *data);
static int		died_while_waiting(t_philo *philo, t_data *data);

/*
	Monitor checks whether a philosopher has died
	or all philosophers have eaten enough.
*/
void	monitor_routine(t_data *data)
{
	int		i;

	while (1)
	{
		usleep(200);
		i = -1;
		while (++i < data->philo_count)
		{
			if (died_while_waiting(&data->philos[i], data))
				return (philo_died(&data->philos[i], data));
			if (data->meals_to_eat != -1
				&& check_all_ate_enough(data->philos, data))
				return ;
		}
	}
	return ;
}

static int	check_all_ate_enough(t_philo *philos, t_data *data)
{
	int		i;
	int		all_ate_enough;

	i = -1;
	all_ate_enough = 1;
	while (all_ate_enough && ++i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].done_mutex);
		if (philos[i].ate_enough == false)
			all_ate_enough = 0;
		pthread_mutex_unlock(&data->philos[i].done_mutex);
	}
	if (all_ate_enough == 1)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->philo_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (all_ate_enough);
}

static void	philo_died(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	if (printf("%zu %d %s\n", time_now(data), philo->id, "died") == -1)
		data->error = 1;
	pthread_mutex_unlock(&data->print_mutex);
	return ;
}

static int	died_while_waiting(t_philo *philo, t_data *data)
{
	int		meals_to_eat;
	int		meals_ate;
	size_t	last_meal;
	size_t	time_to_die;

	meals_to_eat = data->meals_to_eat;
	time_to_die = (size_t)data->time_to_die;
	pthread_mutex_lock(&philo->meal_mutex);
	meals_ate = philo->meals_ate;
	last_meal = time_since_meal(philo);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (meals_to_eat != -1)
		return (meals_ate < meals_to_eat
			&& last_meal >= time_to_die);
	else
		return (last_meal >= time_to_die);
}
