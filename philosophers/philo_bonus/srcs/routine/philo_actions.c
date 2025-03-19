/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:10:26 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/19 14:45:49 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_done_eating(t_philo *philo, t_state *state, size_t *state_start,
	size_t cur_time)
{
	if (cur_time - *state_start >= (size_t)philo->data->time_to_eat)
	{
		unlock_forks(philo->data->forks, 2);
		if (print_msg(philo, "is sleeping") == -1)
			exit(1);
		*state = SLEEPING;
		*state_start = cur_time;
	}
}

void	p_eat(t_philo *philo, t_state *state, size_t *state_start)
{
	wait_if_not_very_hungry(philo);
	sem_wait(philo->data->forks);
	if (print_msg(philo, "has taken a fork") == -1)
	{
		unlock_forks(philo->data->forks, 1);
		exit (1);
	}
	sem_wait(philo->data->forks);
	if (print_msg(philo, "has taken a fork") == -1)
	{
		unlock_forks(philo->data->forks, 2);
		exit (1);
	}
	philo->meals_ate++;
	*state_start = time_now(philo->data);
	philo->last_meal = *state_start;
	*state = EATING;
	if (print_msg(philo, "is eating") == -1)
	{
		unlock_forks(philo->data->forks, 2);
		exit (1);
	}
}

void	p_think(t_philo *philo, t_state *state)
{
	if (print_msg(philo, "is thinking") != -1)
		*state = HUNGRY;
	else
		exit(1);
}

void	p_sleep(t_state *state, size_t time_slept, int time_to_sleep)
{
	if (time_slept >= (size_t)time_to_sleep)
		*state = THINKING;
}
