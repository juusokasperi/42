/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:49:04 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/12 10:59:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	wait_philos(int philos_alive, int status, pid_t pid, t_data *data);

void	wait_children(t_data *data)
{
	int		status;
	pid_t	pid;
	int		philos_alive;

	status = 0;
	pid = 0;
	philos_alive = data->philo_count;
	sem_post(data->sim_lock);
	wait_philos(philos_alive, status, pid, data);
}

int	create_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("create fork failed\n");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	wait_philos(int philos_alive, int status, pid_t pid, t_data *data)
{
	int	i;

	while (philos_alive)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			philos_alive--;
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) == 1)
				{
					i = -1;
					while (++i < data->philo_count)
					{
						if (data->philo_pids[i] != pid)
							kill(data->philo_pids[i], SIGTERM);
					}
					break ;
				}
			}
		}
		else
			break ;
	}
}

void	close_and_unlink_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print_lock);
	sem_close(data->sim_lock);
	sem_unlink("/forks");
	sem_unlink("/print_lock");
	sem_unlink("/sim_lock");
}
