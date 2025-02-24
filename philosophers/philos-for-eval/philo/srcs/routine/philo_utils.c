/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:45:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/24 19:40:24 by jrinta-          ###   ########.fr       */
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
	if (printf("%zu %d %s\n", time_now(philo->data), philo->id, str) == -1)
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

	meals_to_eat = philo->data->meals_to_eat;
	if (meals_to_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	meals_ate = philo->meals_ate;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (meals_ate >= meals_to_eat)
	{
		pthread_mutex_lock(&philo->done_mutex);
		philo->ate_enough = true;
		pthread_mutex_unlock(&philo->done_mutex);
		return (1);
	}
	return (0);
}

/*
	If philosopher is not yet hungry, they wait a bit.
*/
void	wait_if_not_very_hungry(t_philo *philo)
{
	size_t	last_meal;
	size_t	threshold;
	size_t	sleep_time;

	if (philo->data->philo_count % 2 == 0)
		return ;
	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = time_since_meal(philo);
	pthread_mutex_unlock(&philo->meal_mutex);
	threshold = philo->data->time_to_die * 0.75;
	if (last_meal > 0 && threshold > last_meal)
	{
		sleep_time = philo->data->time_to_die - last_meal;
		if (sleep_time >= 5000)
			sleep_time = 5;
		else if (sleep_time >= 1000)
			sleep_time = sleep_time / 1000;
		if (sleep_time > 5)
			usleep(500);
		else
			ft_usleep(sleep_time);
	}
}
