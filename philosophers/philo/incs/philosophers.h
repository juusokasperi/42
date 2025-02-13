/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:11:17 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/13 10:59:45 by jrinta-          ###   ########.fr       */
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

# define PHILOS_MAX 200

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
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
	pthread_mutex_t	forks[PHILOS_MAX];
	pthread_mutex_t	dead_lock;
	t_philo			philos[PHILOS_MAX];
};

//	Init:
int		parse_args(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);
int		init_threads(t_data *data);

//	Exit:
//		Ft_cleanup.c
void	ft_cleanup(t_data *data, char *str);

//	Utils:
//		Ft_error.c
void	ft_error(char *str);
//		Ft_strlen.c
size_t	ft_strlen(char *str);
//		Ft_atoi.c
int		ft_atoi(const char *str);
//		Get_time_ms.c
size_t	get_time_ms(void);
//		Ft_usleep.c
int		ft_usleep(size_t ms);
//		Print_msg.c
void	print_msg(t_philo *philo, char *str);

//	Routines:
//		Monitor.c
void	*monitor_routine(void *arg);
//		Philo_died.c
void	*philo_routine(void *arg);

#endif
