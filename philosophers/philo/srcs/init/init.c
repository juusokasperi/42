/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:04:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/24 14:41:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	fill_data(t_philo *philo, t_data *data, int i);
static int	init_meal_mutex(t_data *data);
static int	init_done_mutex(t_data *data);

/*
	Allocates the philos, initalizes their data and each philos own mutexes;
	meal_mutex and if meals_to_eat is set, done_mutex

	The meal_mutex is used when checking last_meal and meals_ate.
	done_mutex is used to check whether a philosopher has
	set their bool ate_enough to true.
*/
int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (0);
	i = -1;
	while (++i < data->philo_count)
		fill_data(&data->philos[i], data, i);
	if (!init_meal_mutex(data))
		return (0);
	if (data->meals_to_eat != -1 && !init_done_mutex(data))
		return (0);
	return (1);
}

static void	fill_data(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_t	*tmp;

	philo->id = i + 1;
	philo->last_meal = 0;
	philo->meals_ate = 0;
	philo->data = data;
	philo->right_fork = &data->forks[i];
	philo->left_fork = &data->forks[(i + 1) % data->philo_count];
	philo->ate_enough = false;
	if (philo->right_fork > philo->left_fork)
	{
		tmp = philo->right_fork;
		philo->right_fork = philo->left_fork;
		philo->left_fork = tmp;
	}
}

static int	init_meal_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&data->philos[i].meal_mutex);
				pthread_mutex_destroy(&data->forks[i]);
			}
			pthread_mutex_destroy(&data->print_mutex);
			ft_free((void **)data->philos);
			return (0);
		}
	}
	return (1);
}

static int	init_done_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->philos[i].done_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philos[i].done_mutex);
			pthread_mutex_destroy(&data->print_mutex);
			ft_free((void **)data->philos);
			i = -1;
			while (++i < data->philo_count)
			{
				pthread_mutex_destroy(&data->philos[i].meal_mutex);
				pthread_mutex_destroy(&data->forks[i]);
			}
			return (0);
		}
	}
	return (1);
}
