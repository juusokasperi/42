/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:18:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/18 22:51:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		valid_args(int argc, char **argv);
static int		parse_args(t_data *data, int argc, char **argv);
static size_t	ft_strlen(char *s);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(SYNTAX));
	if (!parse_args(&data, argc, argv))
		return (ft_error("Invalid arguments."));
	if (!init_mutexes(&data))
		return (ft_error("Error initializing mutexes."));
	if (!init_philos(&data))
		return (ft_error("Error initializing philosophers."));
	if (!init_threads(&data))
		return (1);
	monitor_routine(&data);
	if (!join_threads(&data))
		return (1);
	return (ft_cleanup(&data));
}

/*
	Parse and set the initial info for the simulation data.
*/
static int	parse_args(t_data *data, int argc, char **argv)
{
	if (!valid_args(argc, argv))
		return (0);
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = 0;
	data->error = 0;
	data->philo_died = 0;
	if (argc == 6)
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = -1;
	if (data->philo_count < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| data->meals_to_eat == 0)
		return (0);
	return (1);
}

/*
	Checks that the arguments contain only digits.
*/
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

int	ft_error(char *str)
{
	printf("%sERROR:%s %s\n", TRED, TRESET, str);
	return (1);
}

static size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
