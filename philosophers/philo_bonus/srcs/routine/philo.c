/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:26:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/19 14:56:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_setup(t_data **data, t_state *state);
static void	handle_one_philo(t_philo *philo);

static void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_ate_enough(philo))
			return (NULL);
		else if (is_dead(philo))
			exit(1);
		usleep(50);
	}
	return (NULL);
}

static void	create_monitor_and_sleep(t_philo *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0
		|| pthread_detach(monitor) != 0)
	{
		sem_wait(philo->data->print_lock);
		exit(1);
	}
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat / 2);
}

void	philo_routine(t_data *data)
{
	t_philo	*philo;
	size_t	cur_time;
	t_state	state;
	size_t	state_start;

	philo = &data->philo[0];
	philo_setup(&data, &state);
	create_monitor_and_sleep(philo);
	while (1)
	{
		cur_time = time_now(data);
		if (state != EATING && philo_ate_enough(philo))
			exit(0);
		if (state == HUNGRY)
			p_eat(philo, &state, &state_start);
		else if (state == EATING)
			p_done_eating(philo, &state, &state_start, cur_time);
		else if (state == SLEEPING)
			p_sleep(&state, cur_time - state_start, data->time_to_sleep);
		else if (state == THINKING)
			p_think(philo, &state);
		usleep(125);
	}
	exit(0);
}

static void	handle_one_philo(t_philo *philo)
{
	sem_wait(philo->data->forks);
	if (is_dead(philo) || print_msg(philo, "has taken a fork") == -1)
	{
		sem_post(philo->data->forks);
		exit (1);
	}
	while (!is_dead(philo))
		ft_usleep(philo->data->time_to_die);
	sem_post(philo->data->forks);
	exit (1);
}

static void	philo_setup(t_data **data, t_state *state)
{
	ft_free((void **)&(*data)->philo_pids);
	(*data)->philo->data = *data;
	(*data)->philo->last_meal = 0;
	(*data)->philo->meals_ate = 0;
	*state = HUNGRY;
	sem_wait((*data)->sim_lock);
	sem_post((*data)->sim_lock);
	(*data)->start_time = get_time_ms();
	(*data)->philo->last_meal = time_now(*data);
	if ((*data)->philo_count == 1)
		return (handle_one_philo(&(*data)->philo[0]));
	printf("Philo %d returning from setup\n", (*data)->philo->id);
}
