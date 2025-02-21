/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:59:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/20 20:44:43 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_success(void);
static bool	check_meals_eaten(t_data *data);

void	ft_cleanup(t_data *data, char *str)
{
	int		philo_died;
	bool	ate_enough_times;

	philo_died = data->philo_died;
	if (data)
		cleanup_mutexes(data);
	ate_enough_times = check_meals_eaten(data);
	if (data->philos)
		ft_free((void **)&data->philos);
	if (str)
		ft_error(str);
	if (data->error)
		ft_error("Write call failed in a thread.");
	if (ate_enough_times == false && philo_died)
		ft_error("Philosopher died.");
	else
		ft_success();
}

static void	ft_success(void)
{
	printf("%sSUCCESS:%s All philosophers have finished eating.\n",
		TGREEN, TRESET);
	exit(0);
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
		{
			printf("philo[%d] has ate %d times, meals to eat is %d\n",i, data->philos[i].meals_ate, data->meals_to_eat);
			return (false);
		}
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
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->print_lock);
	if (data->forks)
		ft_free((void **)&data->forks);
}
