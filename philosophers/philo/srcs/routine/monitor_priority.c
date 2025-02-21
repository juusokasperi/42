/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_priority.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:47:30 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/21 18:24:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_priority_struct(t_priority *id_nums, int i, t_data *data);
static void	priority_for_bigger(t_philo *philos, t_data *data, int i);
static void	priority_for_two(t_philo *philos, t_data *data, int i);

void	check_priority(t_philo *philos, t_data *data, int i)
{
	if (data->philo_count == 1)
		return ;
	else if (data->philo_count == 2)
		priority_for_two(philos, data, i);
	else
		priority_for_bigger(philos, data, i);
}

//	To check in which order we want to lock the mutexes.
//	If checking priority for philo 0, we want to lock their mutex first,
//	then right, then left id (which points to the end of the philos)
//	If checing priority for philo 3 with 3 philos, we need to lock the
//	right id first, then the left id, then the current philo.
static void	set_priority_struct(t_priority *id_nums, int i, t_data *data)
{
	id_nums->left_id = (i + data->philo_count - 1) % data->philo_count;
	id_nums->right_id = (i + 1) % data->philo_count;

	id_nums->first = ft_min_three(id_nums->left_id, i, id_nums->right_id);
	id_nums->second = ft_mid_three(id_nums->left_id, i, id_nums->right_id);
	id_nums->third = ft_max_three(id_nums->left_id, i, id_nums->right_id);
}

//	Determine priority for eating for 3 and more philosophers.
static void	priority_for_bigger(t_philo *philos, t_data *data, int i)
{
	t_priority	id_nums;
	size_t		cur_t;

	set_priority_struct(&id_nums, i, data);
	pthread_mutex_lock(&philos[id_nums.first].meal_mutex);
	pthread_mutex_lock(&philos[id_nums.second].meal_mutex);
	pthread_mutex_lock(&philos[id_nums.third].meal_mutex);
	id_nums.left_meals = philos[id_nums.left_id].meals_ate;
	id_nums.right_meals = philos[id_nums.right_id].meals_ate;
	cur_t = get_time_ms() - data->start_time;
	id_nums.l_last_meal = cur_t - data->philos[id_nums.left_id].last_meal;
	id_nums.r_last_meal = cur_t - data->philos[id_nums.right_id].last_meal;
	if ((cur_t - philos[i].last_meal >= id_nums.l_last_meal)
		&& (cur_t - philos[i].last_meal >= id_nums.r_last_meal))
		philos[i].should_eat_next = 1;
	else
		philos[i].should_eat_next = 0;
	pthread_mutex_unlock(&philos[id_nums.third].meal_mutex);
	pthread_mutex_unlock(&philos[id_nums.second].meal_mutex);
	pthread_mutex_unlock(&philos[id_nums.first].meal_mutex);
}

//	Determine eating priority for two philosophers.
static void	priority_for_two(t_philo *philos, t_data *data, int i)
{
	int		first;
	int		second;
	int		other_id;
	size_t		cur_t;

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
	cur_t = get_time_ms() - data->start_time;
	if (cur_t - philos[i].last_meal >= cur_t - philos[other_id].last_meal
		|| philos[i].meals_ate < philos[other_id].meals_ate)
		philos[i].should_eat_next = 1;
	else
		philos[i].should_eat_next = 0;
	pthread_mutex_unlock(&philos[second].meal_mutex);
	pthread_mutex_unlock(&philos[first].meal_mutex);
}
