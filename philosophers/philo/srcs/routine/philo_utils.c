/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:45:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/23 17:40:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	unlock_forks(pthread_mutex_t *first, pthread_mutex_t *second, int i)
{
	if (first != NULL)
		pthread_mutex_unlock(first);
	if (second != NULL)
		pthread_mutex_unlock(second);
	return (i);
}

int	print_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (-1);
	}
	if (printf("%zu %d %s\n", time_now(philo->data), \
		philo->id, str) == -1)
	{
		philo->data->error = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

int	is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->philo_died)
		is_dead = 1;
	else
		is_dead = 0;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (is_dead);
}

int	philo_ate_enough(t_philo *philo)
{
	int	meals_to_eat;
	int	meals_ate;

	pthread_mutex_lock(&philo->meal_mutex);
		meals_to_eat = philo->data->meals_to_eat;
		meals_ate = philo->meals_ate;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (meals_to_eat == -1)
		return (0);
	return (meals_ate >= meals_to_eat);
}

void	wait_if_not_very_hungry(t_philo *philo)
{
	size_t	last_time_ate;
	size_t	threshold;

	pthread_mutex_lock(&philo->meal_mutex);
	last_time_ate = time_since_meal(philo);
	threshold = philo->data->time_to_die * 0.8;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (last_time_ate > 0 && threshold > last_time_ate)
	{
		if (threshold > 10)
			ft_usleep(3);
		else
			ft_usleep(1);
	}
}
