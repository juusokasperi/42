/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:45:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/19 14:45:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_forks(sem_t *forks, int amount)
{
	while (amount)
	{
		sem_post(forks);
		amount--;
	}
}

int	print_msg(t_philo *philo, char *str)
{
	sem_wait(philo->data->print_lock);
	if (printf("%zu %d %s\n", time_now(philo->data), \
		philo->id, str) == -1)
	{
		sem_post(philo->data->print_lock);
		return (-1);
	}
	sem_post(philo->data->print_lock);
	return (0);
}

int	is_dead(t_philo *philo)
{
	if (time_since_meal(philo) >= (size_t)philo->data->time_to_die)
	{
		sem_wait(philo->data->print_lock);
		printf("%zu %d %s\n", time_now(philo->data), \
			philo->id, "died");
		return (1);
	}
	return (0);
}

int	philo_ate_enough(t_philo *philo)
{
	if (philo->data->meals_to_eat == -1)
		return (0);
	if (philo->meals_ate >= philo->data->meals_to_eat)
		return (1);
	return (0);
}

void	wait_if_not_very_hungry(t_philo *philo)
{
	size_t	last_meal;
	size_t	threshold;
	size_t	sleep_time;

	if (philo->data->philo_count % 2 == 0)
		return ;
	last_meal = time_since_meal(philo);
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
