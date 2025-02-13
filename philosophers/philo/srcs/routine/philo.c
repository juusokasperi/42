/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/12 19:19:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		p_think(t_philo *philo);
static void		p_eat(t_philo *philo);
static void		p_sleep(t_philo *philo);
static int		not_dead(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat / 2);
	while (not_dead(philo))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if (!philo->should_eat_next)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			continue ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		p_eat(philo);
		if (!not_dead(philo))
			return (arg);
		p_sleep(philo);
		p_think(philo);
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

static void	p_think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

static void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a left fork");
	if (philo->data->philo_count == 1)
	{
		while (not_dead(philo))
			ft_usleep(1);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a right fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms() - philo->data->start_time;
	philo->meals_ate++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_msg(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	p_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}
