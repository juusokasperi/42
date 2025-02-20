/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/20 17:36:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		p_think(t_philo *philo);
static int		p_eat(t_philo *philo);
static int		p_sleep(t_philo *philo);
static int		is_dead(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat / 2);
	while (philo->data->error == 0 && !is_dead(philo))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		while (philo->data->philo_count > 1 && !philo->should_eat_next
			&& philo->data->error == 0 && !is_dead(philo))
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			ft_usleep(1);
			pthread_mutex_lock(&philo->meal_mutex);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		if (philo->data->error || is_dead(philo))
			break ;
		if (p_eat(philo) == -1 || p_sleep(philo) == -1 || p_think(philo) == -1)
			break ;
	}
	return (arg);
}

static int	is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->philo_died)
		is_dead = 1;
	else
		is_dead = 0;
	pthread_mutex_unlock(&philo->data->lock);
	return (is_dead);
}

static int	p_think(t_philo *philo)
{
	if (is_dead(philo))
		return (-1);
	if (print_msg(philo, "is thinking") == -1)
		return (-1);
	return (0);
}

static int	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (is_dead(philo))
		return (unlock_forks(philo->left_fork, NULL, -1));
	if (print_msg(philo, "has taken a fork") == -1)
		return (unlock_forks(philo->left_fork, NULL, -1));
	if (philo->data->philo_count == 1)
	{
		while (!is_dead(philo))
			ft_usleep(1);
		return (unlock_forks(philo->left_fork, NULL, 0));
	}
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo))
		return (unlock_forks(philo->right_fork, philo->left_fork, -1));
	if (print_msg(philo, "has taken a fork") == -1)
		return (unlock_forks(philo->right_fork, philo->left_fork, -1));
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms() - philo->data->start_time;
	philo->meals_ate++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (print_msg(philo, "is eating") == -1)
		return (unlock_forks(philo->right_fork, philo->left_fork, -1));
	ft_usleep(philo->data->time_to_eat);
	return (unlock_forks(philo->right_fork, philo->left_fork, 0));
}

static int	p_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return (-1);
	if (print_msg(philo, "is sleeping") == -1)
		return (-1);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}
