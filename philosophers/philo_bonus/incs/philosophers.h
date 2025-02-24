/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:11:17 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/23 14:01:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "terminal_colors.h"

# define SYNTAX "Usage: ./philo n_philos time_to_die \
time_to_eat time_to_sleep [x_each_philo_must_eat]"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	size_t			last_meal;
	int				meals_ate;
}	t_philo;

struct s_data
{
	int				philo_count;
	size_t			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	sem_t			*forks;
	sem_t			*sim_lock;
	sem_t			*print_lock;
	pid_t			*philo_pids;
	t_philo			philo[1];
};

//	Init:
int		parse_args(t_data *data, int argc, char **argv);
int	init_semaphores(t_data *data);
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);
int		init_threads(t_data *data);
int		join_threads(t_data *data);
void	wait_for_start(t_philo *philo);
int		ft_error(char *str);
//	Exit:
//		Ft_cleanup.c
int		ft_cleanup(t_data *data);
void	cleanup_mutexes(t_data *data);
//	Utils:
//		Philo_utils.c
int		is_dead(t_philo *philo);
int		print_msg(t_philo *philo, char *str);
int		unlock_forks(pthread_mutex_t *first, pthread_mutex_t *second, int i);
int		philo_ate_enough(t_philo *philo);
void	wait_if_not_very_hungry(t_philo *philo);
//		Get_time_ms.c
size_t	get_time_ms(void);
size_t	time_now(t_data *data);
size_t	time_since_meal(t_philo *philo);
//		Ft_usleep.c
int		ft_usleep(size_t ms);
//		Ft_atoi.c
int		ft_atoi(const char *str);
//		Ft_free.c
void	*ft_free(void **ptr);
//	Routines:
//		Monitor.c
void	monitor_routine(t_data *data);
//		Philo.c
void	*philo_routine(void *arg);

#endif
