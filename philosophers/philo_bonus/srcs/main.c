/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:18:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/23 16:18:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	close_and_unlink_semaphores(t_data *data);
int		create_fork(void);

void	philo_setup(t_data *data)
{
	pthread_t	monitor;

	free(data->philo_pids);
	sem_wait(data->sim_lock);
	sem_wait(data->print_lock);
	printf("Sim lock opened, id %d!\n", data->philo->id);
	sem_post(data->print_lock);
	sem_post(data->sim_lock);
	if (data->philo->id == 8)
	{
		sem_wait(data->sim_lock);
		sem_wait(data->print_lock);
		printf("Locked sim lock and returning with exit code 1 for philo %d\n", data->philo->id);
		sem_post(data->print_lock);
		exit(1);
	}
	sem_wait(data->sim_lock);
	sem_wait(data->print_lock);
	printf("Returning with exit code 0 for philo %d\n", data->philo->id);
	sem_post(data->print_lock);
	sem_post(data->sim_lock);
	exit (0);
}

void	wait_children(t_data *data)
{
	int		philos_alive;
	int		status;
	pid_t	pid;
	int		i;

	philos_alive = data->philo_count;
	sem_post(data->sim_lock);
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
					printf("%sPhilo %d starved%s, terminating all.\n", TRED, pid, TRESET);
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

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	pid_t	pid;

	if (argc < 5 || argc > 6)
		return (ft_error(SYNTAX));
	if (!parse_args(&data, argc, argv))
		return (ft_error("Invalid arguments."));
	if (init_semaphores(&data) == -1)
		return (1);
	i = -1;
	while (++i < data.philo_count)
	{
		data.philo->id++;
		pid = create_fork();
		if (pid == 0)
			philo_setup(&data);
		data.philo_pids[i] = pid;
	}
	printf("Main process done with forks, opening sim lock\n");
	wait_children(&data);
	close_and_unlink_semaphores(&data);
	free(data.philo_pids);
	return (0);
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

int	ft_error(char *str)
{
	printf("%sERROR:%s %s\n", TRED, TRESET, str);
	return (1);
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
