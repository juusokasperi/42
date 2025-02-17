/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/17 15:59:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		p_think(t_philo *philo);
static int		p_eat(t_philo *philo);
static int		p_sleep(t_philo *philo);
static int		not_dead(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat / 2);
	while (philo->data->error == 0 && philo->data->philo_died == 0
		&& not_dead(philo))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if (!philo->should_eat_next)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			continue ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		if (p_eat(philo) == -1 || !not_dead(philo)
			|| p_sleep(philo) == -1 || p_think(philo) == -1)
			break ;
	}
	return (arg);
}

static int	not_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->data->dead_lock);
	is_dead = philo->data->philo_died;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (!is_dead);
}

static int	p_think(t_philo *philo)
{
	if (print_msg(philo, "is thinking") == -1)
		return (-1);
	return (0);
}

static int	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_msg(philo, "has taken a left fork") == -1)
		return (unlock_fork(philo->left_fork, NULL, -1));
	if (philo->data->philo_count == 1)
	{
		while (not_dead(philo))
			ft_usleep(1);
		return (unlock_fork(philo->left_fork, NULL, 0));
	}
	pthread_mutex_lock(philo->right_fork);
	if (print_msg(philo, "has taken a right fork") == -1)
		return (unlock_fork(philo->right_fork, philo->left_fork, -1));
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms() - philo->data->start_time;
	philo->meals_ate++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (print_msg(philo, "is eating") == -1)
		return (unlock_fork(philo->right_fork, philo->left_fork, -1));
	ft_usleep(philo->data->time_to_eat);
	return (unlock_fork(philo->right_fork, philo->left_fork, 0));
}

static int	p_sleep(t_philo *philo)
{
	if (print_msg(philo, "is sleeping") == -1)
		return (-1);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}
