/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:08 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/03 23:39:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		*philo_died(t_philo *philos, t_data *data, int i);
static void	check_priority(t_philo *philos, t_data *data, int i);

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		i;
	size_t	time;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			time = get_time_ms() - data->start_time;
			if ((time - philos[i].last_meal) >= (size_t)data->time_to_die)
				return (philo_died(philos, data, i));
			check_priority(philos, data, i);
			pthread_mutex_unlock(&philos[i].meal_mutex);
		}
		ft_usleep(1);
	}
	return (arg);
}

void	*philo_died(t_philo *philos, t_data *data, int i)
{
	pthread_mutex_lock(&data->dead_lock);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->dead_lock);
	pthread_mutex_unlock(&philos[i].meal_mutex);
	print_msg(&philos[i], "died");
	return (NULL);
}

static void	check_priority(t_philo *philos, t_data *data, int i)
{
	int	left_id;
	int	right_id;
	int	left_meals;
	int	right_meals;

	left_id = (i + data->philo_count - 1) % data->philo_count;
	right_id = (i + 1) % data->philo_count;
	pthread_mutex_lock(&philos[left_id].meal_mutex);
	left_meals = philos[left_id].meals_ate;
	pthread_mutex_unlock(&philos[left_id].meal_mutex);
	pthread_mutex_lock(&philos[right_id].meal_mutex);
	right_meals = philos[right_id].meals_ate;
	pthread_mutex_unlock(&philos[right_id].meal_mutex);
	if (philos[i].meals_ate < left_meals &&
		philos[i].meals_ate < right_meals)
		philos[i].should_eat_next = 1;
}
