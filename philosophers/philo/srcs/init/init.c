/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:04:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/21 19:54:22 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	valid_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
	}
	return (1);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	if (!valid_args(argc, argv))
		return (0);
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->error = 0;
	data->philo_died = 0;
	if (argc == 6)
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = -1;
	if (data->philo_count < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
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
	philo->should_eat_next = 1;
	if (philo->right_fork > philo->left_fork)
	{
		tmp = philo->right_fork;
		philo->right_fork = philo->left_fork;
		philo->left_fork = tmp;
	}
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (0);
	i = -1;
	while (++i < data->philo_count)
	{
		fill_data(&data->philos[i], data, i);
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
