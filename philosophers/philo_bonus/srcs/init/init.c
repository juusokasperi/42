/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:04:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/18 23:17:03 by jrinta-          ###   ########.fr       */
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
		if (ft_strlen(argv[i]) > 10
			|| (ft_strlen(argv[i]) == 10 && argv[i][9] > 7))
			return (0);
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
	}
	return (1);
}

void	unlink_semaphores(char *lock, char *lock_2, char *lock_3)
{
	if (lock != NULL)
		sem_unlink(lock);
	if (lock_2 != NULL)
		sem_unlink(lock_2);
	if (lock_3 != NULL)
		sem_unlink(lock_3);
}

int	init_semaphores(t_data *data)
{
	unlink_semaphores("/forks", "/print_lock", "/sim_lock");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->philo_count);
	if (data->forks == SEM_FAILED)
	{
		printf("Error: sem_open forks failed\n");
		ft_free((void **)&data->philo_pids);
		return (-1);
	}
	data->sim_lock = sem_open("/sim_lock", O_CREAT, 0644, 0);
	if (data->sim_lock == SEM_FAILED)
	{
		unlink_semaphores("/forks", NULL, NULL);
		printf("Error: sem_open sim_lock failed\n");
		ft_free((void **)&data->philo_pids);
		return (-1);
	}
	data->print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
	if (data->print_lock == SEM_FAILED)
	{
		unlink_semaphores("/forks", "/sim_lock", NULL);
		printf("Error: sem_open sim_lock failed\n");
		ft_free((void **)&data->philo_pids);
		return (-1);
	}
	return (0);
}

int	allocate_pids(t_data *data)
{
	int	i;

	data->philo_pids = malloc(data->philo_count * sizeof(pid_t));
	if (!data->philo_pids)
		return (-1);
	i = -1;
	while (++i < data->philo_count)
		data->philo_pids[i] = 0;
	return (0);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	if (!valid_args(argc, argv))
		return (0);
	data->philo_count = ft_atoi(argv[1]);
	data->start_time = 0;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = -1;
	data->philo->id = 0;
	data->philo->last_meal = 0;
	data->philo->meals_ate = 0;
	if (data->philo_count < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| data->meals_to_eat == 0)
		return (0);
	if (allocate_pids(data) == -1)
		return (0);
	return (1);
}
