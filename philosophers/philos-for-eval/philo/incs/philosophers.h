/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:11:17 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/24 15:30:01 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
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
	bool			ate_enough;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	done_mutex;
	t_data			*data;
}	t_philo;

struct s_data
{
	int				philo_count;
	size_t			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				philo_died;
	_Atomic int		error;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
};

//	Init:
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);
int		init_threads(t_data *data);
int		join_threads(t_data *data);
void	wait_for_start(t_philo *philo);
int		ft_error(char *str);
//		Ft_cleanup.c
int		ft_cleanup(t_data *data);
void	cleanup_mutexes(t_data *data);
//	Routines:
//		Monitor.c
void	monitor_routine(t_data *data);
//		Philo.c
void	*philo_routine(void *arg);
//		Philo_utils.c
int		is_dead(t_philo *philo);
int		print_msg(t_philo *philo, char *str);
int		unlock_forks(pthread_mutex_t *first, pthread_mutex_t *second, int i);
int		philo_ate_enough(t_philo *philo);
void	wait_if_not_very_hungry(t_philo *philo);
//		Utils.c
size_t	get_time_ms(void);
size_t	time_now(t_data *data);
size_t	time_since_meal(t_philo *philo);
int		ft_usleep(size_t ms);
void	*ft_free(void **ptr);
//		Ft_atoi.c
int		ft_atoi(const char *str);

#endif
