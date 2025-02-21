/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:11:17 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/21 23:57:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <limits.h>
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
	int				should_eat_next;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
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

//	Monitor uses this struct to determine the right
//	order for locking philosopher's meal mutexes.
typedef struct s_priority
{
	int		left_id;
	int		right_id;
	int		left_meals;
	int		right_meals;
	size_t	l_last_meal;
	size_t	r_last_meal;
	int		first;
	int		second;
	int		third;
}	t_priority;

//	Init:
int		parse_args(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);
int		init_threads(t_data *data);
int		join_threads(t_data *data);
void	wait_for_start(t_philo *philo);
//	Exit:
//		Ft_cleanup.c
void	ft_cleanup(t_data *data, char *str);
void	cleanup_mutexes(t_data *data);

//	Utils:
//		Is_dead.c
int		is_dead(t_philo *philo);
//		Ft_error.c
void	ft_error(char *str);
//		Ft_strlen.c
size_t	ft_strlen(char *str);
//		Ft_atoi.c
int		ft_atoi(const char *str);
//		Ft_free.c
void	*ft_free(void **ptr);
//		Get_time_ms.c
size_t	get_time_ms(void);
//		Ft_usleep.c
int		ft_usleep(size_t ms);
//		Print_msg.c
int		print_msg(t_philo *philo, char *str);
//		Min_max_mid.c
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_min_three(int a, int b, int c);
int		ft_mid_three(int a, int b, int c);
int		ft_max_three(int a, int b, int c);
//		Ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);
//		Monitor_priority_utils.c
void	check_priority(t_philo *philos, t_data *data, int i);
//		Philo_unlock_forks.c
int		unlock_forks(pthread_mutex_t *first, pthread_mutex_t *second, int i);
//	Routines:
//		Monitor.c
void	monitor_routine(t_data *data);
//		Philo_died.c
void	*philo_routine(void *arg);
int		is_dead(t_philo *philo);

#endif
