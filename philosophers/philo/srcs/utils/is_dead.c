/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:47:25 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/21 23:44:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	int	is_dead;
	size_t	time_since_meal;

	pthread_mutex_lock(&philo->data->death_mutex);
	time_since_meal = get_time_ms() - philo->data->start_time \
		- philo->last_meal;
	if (time_since_meal >= (size_t)philo->data->time_to_die)
		philo->data->philo_died = 1;
	if (philo->data->philo_died)
		is_dead = 1;
	else
		is_dead = 0;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (is_dead);
}
