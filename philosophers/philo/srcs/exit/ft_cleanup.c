/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:59:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/22 13:52:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_end(char *str);
static bool	check_meals_eaten(t_data *data);

int	ft_cleanup(t_data *data)
{
	int		philo_died;
	bool	ate_enough_times;

	philo_died = data->philo_died;
	if (data)
		cleanup_mutexes(data);
	ate_enough_times = check_meals_eaten(data);
	if (data->philos)
		ft_free((void **)&data->philos);
	if (data->error)
		return (ft_error("Write call failed in a thread."));
	if (ate_enough_times == false && philo_died)
		return (ft_end("Simulation ended, a philosopher has starved."));
	else
		return (ft_end("Simulation ended, philosophers have finished eating."));
}

static int	ft_end(char *str)
{
	printf("%sEND:%s %s\n",
		TYELLOW, TRESET, str);
	return (0);
}

static bool	check_meals_eaten(t_data *data)
{
	int	i;

	if (data->meals_to_eat == -1)
		return (false);
	i = -1;
	while (++i < data->philo_count)
	{
		if (data->philos[i].meals_ate < data->meals_to_eat)
			return (false);
	}
	return (true);
}

void	cleanup_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	if (data->forks)
		ft_free((void **)&data->forks);
}
