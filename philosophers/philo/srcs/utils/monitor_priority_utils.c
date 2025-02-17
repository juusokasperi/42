/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_priority_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:47:30 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/17 13:48:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	To check in which order we want to lock the mutexes.
//	If checking priority for philo 0, we want to lock their mutex first,
//	then right, then left id (which points to the end of the philos)
//	If checing priority for philo 3 with 3 philos, we need to lock the
//	right id first, then the left id, then the current philo.
void	set_priority_struct(t_priority *id_nums, int i, t_data *data)
{
	id_nums->left_id = (i + data->philo_count - 1) % data->philo_count;
	id_nums->right_id = (i + 1) % data->philo_count;
	if (id_nums->right_id < i)
	{
		id_nums->first = id_nums->right_id;
		id_nums->second = id_nums->left_id;
		id_nums->third = i;
	}
	else if (id_nums->left_id > i)
	{
		id_nums->first = i;
		id_nums->second = id_nums->right_id;
		id_nums->third = id_nums->left_id;
	}
	else
	{
		id_nums->first = id_nums->left_id;
		id_nums->second = i;
		id_nums->third = id_nums->right_id;
	}
}

void	priority_for_two(t_philo *philos, t_data *data, int i)
{
	int	first;
	int	second;
	int	other_id;

	other_id = (i + 1) % data->philo_count;
	if (other_id < i)
	{
		first = other_id;
		second = i;
	}
	else
	{
		first = i;
		second = other_id;
	}
	pthread_mutex_lock(&philos[first].meal_mutex);
	pthread_mutex_lock(&philos[second].meal_mutex);
	if (philos[i].meals_ate < philos[other_id].meals_ate)
		philos[i].should_eat_next = 1;
	pthread_mutex_unlock(&philos[second].meal_mutex);
	pthread_mutex_unlock(&philos[first].meal_mutex);
}
